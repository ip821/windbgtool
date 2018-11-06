#include "stdafx.h"
#include "Dump.h"

CDump::CDump()
{
}

CDump::~CDump()
{
}

STDMETHODIMP CDump::CreateDump(DWORD dwProcessId, BSTR bstrFilePath)
{
	HRESULT hr = S_OK;

	HANDLE hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		dwProcessId
	);

	if (!hProcess)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	HANDLE hDumpFile = CreateFile(
		bstrFilePath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hDumpFile == INVALID_HANDLE_VALUE)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		goto Exit;
	}

	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		BOOL bRes = MiniDumpWriteDump(
			hProcess,
			dwProcessId,
			hDumpFile,
			(MINIDUMP_TYPE)(MiniDumpWithFullMemory | MiniDumpWithHandleData | MiniDumpWithUnloadedModules | MiniDumpWithThreadInfo | MiniDumpWithFullMemoryInfo | MiniDumpWithDataSegs | MiniDumpWithPrivateReadWriteMemory),
			NULL,
			NULL,
			NULL
		);
		if(!bRes)
			hr = HRESULT_FROM_WIN32(GetLastError());
	}

	CloseHandle(hDumpFile);

Exit:
	CloseHandle(hProcess);
	return hr;
}

STDMETHODIMP CDump::CopyDlls(DWORD dwProcessId, BSTR bstrPath)
{
	HRESULT hr = S_OK;

	CHandle hProcess(
		OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE,
			dwProcessId
		)
	);
	
	if (!hProcess)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	DWORD cbNeeded = 0;
	BOOL bRes = EnumProcessModules(hProcess, NULL, 0, &cbNeeded);
	if (!bRes)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	CAutoVectorPtr<HMODULE> pBuffer;
	if (!pBuffer.Allocate(cbNeeded))
	{
		return E_OUTOFMEMORY;
	}

	bRes = EnumProcessModules(hProcess, &pBuffer[0], cbNeeded * sizeof(HMODULE), &cbNeeded);
	if (!bRes) 
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	for (UINT i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
	{
		TCHAR szModName[MAX_PATH] = { 0 };
		if (!GetModuleFileNameEx(hProcess, pBuffer[i], szModName, MAX_PATH))
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		CString strFilename = CString(PathFindFileName(szModName)).MakeLower();
		if (strFilename == _T("clr.dll"))
		{
			PathRemoveFileSpec(szModName);
			CComBSTR bstrSourceFolder(szModName);
			CComBSTR bstrDestFolder(bstrPath);

			hr = CopyFileImpl(bstrSourceFolder, bstrDestFolder, CComBSTR(L"clr.dll"));
			if (FAILED(hr))
				return hr;

			hr = CopyFileImpl(bstrSourceFolder, bstrDestFolder, CComBSTR(L"mscordacwks.dll"));
			if (FAILED(hr))
				return hr;

			hr = CopyFileImpl(bstrSourceFolder, bstrDestFolder, CComBSTR(L"sos.dll"));
			if (FAILED(hr))
				return hr;
		}
	}

	return S_OK;
}

STDMETHODIMP CDump::CopyFileImpl(BSTR bstrSourceFolderPath, BSTR bstrDestinationFolderPath, BSTR bstrFileName)
{
	CString strSourceFileName;
	{
		LPTSTR lpszSourcePath = strSourceFileName.GetBuffer(MAX_PATH);
		PathCombine(lpszSourcePath, bstrSourceFolderPath, bstrFileName);
		strSourceFileName.ReleaseBuffer();
	}

	CString strDestFileName;
	{
		LPTSTR lpszDestPath = strDestFileName.GetBuffer(MAX_PATH);
		PathCombine(lpszDestPath, bstrDestinationFolderPath, bstrFileName);
		strDestFileName.ReleaseBuffer();
	}

	if (!CopyFile(strSourceFileName, strDestFileName, TRUE))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}

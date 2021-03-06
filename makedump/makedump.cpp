// makedump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PathLogic.h"
#include "Dump.h"

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		std::wcout << L"usage: makedump <pid>" << std::endl;
		return -1;
	}

	DWORD dwProcessId = atoi(argv[1]);
	CPathLogic::Init(NULL, TRUE);

	CString strPath;
	HRESULT hr = CPathLogic::FormatWithTime(_T("memory-%s.dmp"), strPath);
	if (FAILED(hr))
	{
		std::wcout << L"Failed to create directory structure" << std::endl;
		return 1;
	}

	CDump dumper;
	hr = dumper.CreateDump(dwProcessId, CComBSTR(strPath));
	if (FAILED(hr))
	{
		std::wcout << L"Failed to create memory dump" << std::endl;
		return 2;
	}

	hr = dumper.CopyDlls(dwProcessId, CComBSTR(CPathLogic::m_strPath));
	if (FAILED(hr)) 
	{
		std::wcout << L"Failed to copy DLL files" << std::endl;
		return 3;
	}

	std::wcout << strPath.GetString() << std::endl;

    return 0;
}


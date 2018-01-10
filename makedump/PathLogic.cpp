#include "stdafx.h"
#include "PathLogic.h"

CString CPathLogic::m_strPath;
CString CPathLogic::m_strTime;

HRESULT CPathLogic::GetContainerPath(CString& str)
{
	TCHAR lpszPath[MAX_PATH];
	if(!GetCurrentDirectory(MAX_PATH, lpszPath))
		return HRESULT_FROM_WIN32(GetLastError());

	PathAppend(lpszPath, CONTAINER_FOLDER_PATH);
	if(!PathFileExists(lpszPath))
	{
		if(!CreateDirectory(lpszPath, NULL))
			return HRESULT_FROM_WIN32(GetLastError());
	}

	str = lpszPath;
	return S_OK;
}

HRESULT CPathLogic::CreateFoldersImpl(BOOL makeSeparateDirectory)
{
	CString strPath = m_strPath;
	HRESULT hr = S_OK;
	if(strPath.IsEmpty())
	{
		hr = GetContainerPath(strPath);

		if(FAILED(hr))
			return hr;
	}

	CString strCurrentTime;
	hr = GetCurrentTimeAsString(strCurrentTime);

	if(FAILED(hr))
		return hr;

	if(makeSeparateDirectory)
	{
		{
			CString strDirName;
			strDirName.Format(_T("dump-%s"), strCurrentTime);
			LPTSTR lpszPath = strPath.GetBuffer(MAX_PATH);
			PathAppend(lpszPath, strDirName);
			strPath.ReleaseBuffer();
		}

		if(!PathFileExists(strPath))
		{
			if(!CreateDirectory(strPath, NULL))
			{
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}
	}

	m_strPath = strPath;
	return S_OK;
}

HRESULT CPathLogic::GetCurrentTimeAsString(CString& str)
{
	const CString strDateFormat = _T("yy''MM''dd");
	const CString strTimeFormat = _T("HH''mm''ss");

	CString strDate;

	int iSize = GetDateFormat(
		LOCALE_USER_DEFAULT,
		0,
		NULL,
		strDateFormat,
		NULL,
		0
		);

	if(!iSize)
		return HRESULT_FROM_WIN32(GetLastError());

	{
		LPTSTR lpszBuffer = strDate.GetBuffer(iSize);
		iSize = GetDateFormat(
			LOCALE_USER_DEFAULT,
			0,
			NULL,
			strDateFormat,
			lpszBuffer,
			iSize
			);
		strDate.ReleaseBuffer();
	}

	if(!iSize)
		return HRESULT_FROM_WIN32(GetLastError());

	CString strTime;
	iSize = GetTimeFormat(
		LOCALE_USER_DEFAULT,
		0,
		NULL,
		strTimeFormat,
		NULL,
		0
		);

	if(!iSize)
		return HRESULT_FROM_WIN32(GetLastError());

	{
		LPTSTR lpszBuffer = strTime.GetBuffer(iSize);
		iSize = GetTimeFormat(
			LOCALE_USER_DEFAULT,
			0,
			NULL,
			strTimeFormat,
			lpszBuffer,
			iSize
			);
		strTime.ReleaseBuffer();
	}

	if(!iSize)
		return HRESULT_FROM_WIN32(GetLastError());

	str = strDate + _T("_") + strTime;
	return S_OK;
}

CPathLogic::CPathLogic()
{
}

HRESULT CPathLogic::Init(LPCTSTR lpszDirPath, BOOL makeSeparateDir)
{
	HRESULT hr = S_OK;
	m_strPath = lpszDirPath;

	hr = CreateFoldersImpl(makeSeparateDir);
	if(FAILED(hr))
		return hr;

	hr = GetCurrentTimeAsString(m_strTime);
	if(FAILED(hr))
		return hr;

	return hr;
}

HRESULT CPathLogic::FormatWithTime(LPCTSTR  strTemplate, CString& strResult)
{
	strResult = m_strPath;
	CString strFileName;
	strFileName.Format(strTemplate, m_strTime);
	{
		LPTSTR lpszPath = strResult.GetBuffer(MAX_PATH);
		PathAppend(lpszPath, strFileName);
		strResult.ReleaseBuffer();
	}
	return S_OK;
}
#pragma once

#define CONTAINER_FOLDER_PATH _T("dumps")

class CPathLogic
{
private:
	CPathLogic();

	static HRESULT GetContainerPath(CString& str);
	static HRESULT CreateFoldersImpl(BOOL makeSeparateDirectory = FALSE);
	static HRESULT GetCurrentTimeAsString(CString& str);

	static CString m_strTime;

public:
	static CString m_strPath;
	static HRESULT Init(LPCTSTR lpszDirPath, BOOL makeSeparateDir = FALSE);
	static HRESULT FormatWithTime(LPCTSTR  strTemplate, CString& strResult);
};

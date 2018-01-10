#pragma once
class CDump
{
private:
	STDMETHOD(CopyFileImpl)(BSTR bstrSourceFolderPath, BSTR bstrDestinationFolderPath, BSTR bstrFileName);
public:
	CDump();
	~CDump();

	STDMETHOD(CreateDump)(DWORD dwProcessId, BSTR bstrFolderPath);
	STDMETHOD(CopyDlls)(DWORD dwProcessId, BSTR bstrPath);
};


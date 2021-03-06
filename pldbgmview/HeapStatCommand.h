// HeapStatCommand.h : Declaration of the CHeapStatCommand

#pragma once
#include "resource.h"       // main symbols
#include "pldbgmview_i.h"

using namespace ATL;


// CHeapStatCommand

class ATL_NO_VTABLE CHeapStatCommand :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHeapStatCommand, &CLSID_HeapStatCommand>,
	public ICommand2,
	public IInitializeWithControlImpl
{
public:
	CHeapStatCommand()
	{
	}

	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(CHeapStatCommand)
		COM_INTERFACE_ENTRY(ICommand)
		COM_INTERFACE_ENTRY(ICommand2)
		COM_INTERFACE_ENTRY(IInitializeWithControl)
	END_COM_MAP()

public:

	STDMETHOD(GetCommandText)(REFGUID guidId, BSTR* bstrText)
	{
		UNREFERENCED_PARAMETER(guidId);
		CHECK_E_POINTER(bstrText);
		*bstrText = CComBSTR(L"CLR Heap stat").Copy();
		return S_OK;
	}

	STDMETHOD(Invoke)(REFGUID guidId)
	{
		UNREFERENCED_PARAMETER(guidId);
		CComQIPtr<IServiceProvider> pServiceProvider =  m_pControl;
		if(!pServiceProvider)
			return E_NOINTERFACE;

		CComPtr<IDebugFormManager> pDebugFormManager;
		RETURN_IF_FAILED(pServiceProvider->QueryService(SERVICE_DEBUG_FORM_MANAGER, IID_IDebugFormManager, (LPVOID*)&pDebugFormManager));
		RETURN_IF_FAILED(pDebugFormManager->OpenForm(DBGCOMMAND_HEAPSTAT, NULL));
		return S_OK;
	}

	STDMETHOD(InstallMenu)(IMenu* pMenu)
	{
		CHECK_E_POINTER(pMenu);
		return pMenu->AddMenuCommand(COMMAND_COMMANDS, COMMAND_HEAPSTAT, this);
	}

	STDMETHOD(GetEnabled)(REFGUID guidId, BOOL* pbEnabled)
	{
		UNREFERENCED_PARAMETER(guidId);
		CHECK_E_POINTER(pbEnabled);
		CComQIPtr<IServiceProvider> pServiceProvider =  m_pControl;
		if(!pServiceProvider)
			return E_NOINTERFACE;

		CComPtr<ICommand2> pCommand2;
		RETURN_IF_FAILED(pServiceProvider->QueryService(COMMAND_OPENDUMP, IID_ICommand2, (LPVOID*)&pCommand2));
		RETURN_IF_FAILED(pCommand2->GetEnabled(COMMAND_OPENDUMP, pbEnabled));
		*pbEnabled = !*pbEnabled;
		return S_OK;
	}

	STDMETHOD(GetHBITMAP)(REFGUID guidId, HBITMAP* pHBITMAP)
	{
		UNREFERENCED_PARAMETER(guidId);
		UNREFERENCED_PARAMETER(pHBITMAP);
		return E_NOTIMPL;
	}

	STDMETHOD(InstallToolbar)(IToolbar* pToolbar)
	{
		UNREFERENCED_PARAMETER(pToolbar);
		return E_NOTIMPL;
	}


};

OBJECT_ENTRY_AUTO(__uuidof(HeapStatCommand), CHeapStatCommand)

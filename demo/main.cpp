#include "stdafx.h"

#include "base/Cef3/browser/main_message_loop.h"
#include "base/Cef3/common/cef_main.h"
#include "main/WndSimpleFrame.h"

template <class T>
void CreateMainWnd(LPCTSTR pstrName)
{
	CWindowWnd *mainFrame = new T;
	mainFrame->Create(NULL, pstrName,  WS_POPUP | WS_THICKFRAME, 0, 0, 0, -1, -1);
	mainFrame->CenterWindow();
	mainFrame->ShowWindow();
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{ 
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ------------------cef��ʼ��------------------
	CCefMainHandler cefHandler;
	if (!cefHandler.Initialize(hInstance, true))
	{ 
		return -1;
	}

	// ------------------duilib��ʼ��------------------
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("Skin\\"));
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		return -1;
	}
	
	// ------------------��ʾ������------------------
	CreateMainWnd<CWndSimpleFrame>(_T("SimpleWnd"));

	// ------------------������Ϣѭ��------------------
	// �������Ϣѭ��ģʽ
	if (cefHandler.m_multi_threaded_message_loop)
	{
		CMainMessageLoopWin main_message_loop;
		main_message_loop.Run();
	}
	else
	{
		CefRunMessageLoop();
	}
	

	// ------------------�����ر���Դ------------------
	cefHandler.Shutdown();

	::CoUninitialize();
	
	return 0;
}

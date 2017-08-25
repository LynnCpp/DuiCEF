#pragma once

#include "../browser/client_browser_app.h"
#include "../renderer/client_renderer_app.h"

class CCefMainHandler: public CefBase
{
public:

	bool Initialize(HINSTANCE hInstance, bool _multi_threaded_message_loop)
	{
		m_multi_threaded_message_loop = _multi_threaded_message_loop;

		CefMainArgs args(hInstance);

		// ��ȡ��������
		ClientApp::ProcessType processType = ClientApp::GetProcessType();

		// ���ݽ�����������ͬ��CefAppʵ��
		CefRefPtr<CefApp> app;

		// browser���̣�����ClientAppBrowserʵ��
		if (processType == ClientApp::ProcessType::BrowserProcess)
		{
			app = new ClientAppBrowser;
		}
		// render���̣�����ClientAppRenderʵ��
		else if (processType == ClientApp::ProcessType::RendererProcess)
		{
			app = new ClientAppRender;
		}
		// �������̣�����ClientAppʵ��
		else
		{
			app = new ClientApp;
		}

		// �ӽ���������������ֱ���˳�
		int exit_code = CefExecuteProcess(args, app.get(), NULL);
		if (exit_code >= 0)
		{
			exit(exit_code);
		}

		CefSettings settings;
		CefSettingsTraits::init(&settings);
		settings.log_severity = LOGSEVERITY_DISABLE;
		settings.multi_threaded_message_loop = _multi_threaded_message_loop;
		CefString(&settings.locale).FromWString(L"zh-CN");

		return CefInitialize(args, settings, app.get(), NULL);
	}

	void Shutdown()
	{
		CefShutdown();
	}

	~CCefMainHandler()
	{
		Shutdown();
	}

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(CCefMainHandler);

public:
	bool m_multi_threaded_message_loop;
};
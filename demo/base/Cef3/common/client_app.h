#pragma once

#include "include/cef_app.h"

class ClientApp
	: public CefApp
{
public:
	enum ProcessType
	{
		BrowserProcess,
		RendererProcess,
		ZygoteProcess,
		OtherProcess,
	};

	//�Զ��巽��
	//��ȡ��������
	static ProcessType GetProcessType();

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(ClientApp);
};
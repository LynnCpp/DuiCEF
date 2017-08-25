#pragma once

#include "../common/client_app.h"

#include "include/base/cef_callback.h"
#include "include/base/cef_bind.h"

#include <queue>

//
#define REQUIRE_MAIN_THREAD   CHECK(CMainMessageLoopWin::GetMainMessageLoop()->RunsTasksOnCurrentThread());

#define PostMainThreadTask(task) \
	CMainMessageLoopWin::GetMainMessageLoop()->PostClosure(task)

#define RunsTasksOnMainThread \
	CMainMessageLoopWin::GetMainMessageLoop()->RunsTasksOnCurrentThread()

class CMainMessageLoopWin
{
public:

	CMainMessageLoopWin();
	~CMainMessageLoopWin();

	int Run();
	void Quit();
	void PostTask(CefRefPtr<CefTask> task);
	void PostClosure(const base::Closure& closure);
	bool RunsTasksOnCurrentThread() const{ return _thread_id == GetCurrentThreadId(); }

private:
	// Create the message window.
	static HWND CreateMessageWindow(HINSTANCE hInstance);

	// Window procedure for the message window.
	static LRESULT CALLBACK MessageWndProc(HWND hWnd, UINT message, WPARAM wParam,
		LPARAM lParam);


	void PostTaskInternal(CefRefPtr<CefTask> task);
	CefRefPtr<CefTask> CefCreateClosureTask(const base::Closure& closure);

	// Must be protected by |_mutex|.
	std::mutex _mutex;
	HWND _message_hwnd_;
	std::queue<CefRefPtr<CefTask>> queued_tasks_;

	UINT _message_id;

	DWORD _thread_id;

	DISALLOW_COPY_AND_ASSIGN(CMainMessageLoopWin);

public:
	static CMainMessageLoopWin* GetMainMessageLoop(){ DCHECK(g_main_message_loop != nullptr); return g_main_message_loop; }

private:
	static CMainMessageLoopWin*  g_main_message_loop;
};
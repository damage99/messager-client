#include "messager.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	Main
	{
		Form* main = new Form(hInstance, "FORM", 100);

		MSG msg;
		HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
		BOOL bRet = 0;
		while (bRet = GetMessage(&msg, nullptr, 0, 0))
		{
			if (-1 == bRet)
				break;

			if (!TranslateAccelerator(main->get_HWND(), hAccel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	ListeningSocket
	{

	}

	return 1;
}

LRESULT Form::ON_CREATE(HWND hWNd, UINT message)
{
	TrayIcon = { 0 };
	TrayIcon.cbSize = sizeof(NOTIFYICONDATA);
	TrayIcon.hWnd = this->hWnd;
	TrayIcon.uVersion = NOTIFYICON_VERSION;
	TrayIcon.uCallbackMessage = WM_USER;
	TrayIcon.hIcon = this->Icon;
	TrayIcon.uFlags = NIF_MESSAGE | NIF_ICON;
	Shell_NotifyIcon(NIM_ADD, &TrayIcon);

	return Form::CALLBACK_RET_DEFAULT;
}

LRESULT Form::ON_PAINT(HWND hWnd, UINT message)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);

	return Form::CALLBACK_RET_DEFAULT;
}

LRESULT Form::ON_QUERYENDSESSION(HWND hWnd, UINT message)
{
	Shell_NotifyIcon(NIM_DELETE, &this->TrayIcon);
	PostQuitMessage(0);

	return Form::CALLBACK_RET_DEFAULT;
}
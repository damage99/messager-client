#include "messager.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Main
	{
		nCmdShow = 0;
		HICON Icon = LoadIcon(hInstance, MAKEINTRESOURCEW(100));
		NOTIFYICONDATA Tray = { 0 };

		Form* main = new Form(hInstance, nCmdShow, "FORM", "LOGIN_MAIN", "ВНИМАНИЕ", Icon, Tray);

		Shell_NotifyIcon(NIM_DELETE, &Tray);
	}

	return 1;
}
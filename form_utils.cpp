#include "includes.hpp"

using std::string;

Application_Properties::Application_Properties()
{
	windowSize.width = GetSystemMetrics(SM_CXSCREEN);
	windowSize.height = GetSystemMetrics(SM_CYSCREEN);
}

void Form_Object::Calc_Size(int width, int height, SizePos ownerSize)
{
	this->size.width = utils::getPercents(ownerSize.width, width);
	this->size.height = utils::getPercents(ownerSize.height, height);

	return (void)0;
}

void Form_Object::Calc_Pos(int x, int y, SizePos ownerSize)
{
	this->pos.x = (x == _FORM_ALIGN_CENTER) ? utils::getCenter(ownerSize.width, this->size.width) : utils::getPercents(ownerSize.width, x);
	this->pos.y = (y == _FORM_ALIGN_CENTER) ? utils::getCenter(ownerSize.height, this->size.height) : utils::getPercents(ownerSize.height, y);

	return (void)0;
}

HWND Form_Object::Create_Elem(HWND hWnd, HINSTANCE Inst, bool createType)
{
	DWORD style;
	HMENU lol;

	if (this->type == "FORM")
	{
		lol = nullptr;
		style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU;
	}
	else
	{
		lol = (HMENU)this->id;
		style = WS_CHILD | WS_VISIBLE;
	}

	return
		createType ?
		extendElem(0x00000200, this->type.c_str(), this->value.c_str(), 0x50010080, this->pos.x, this->pos.y, this->size.width, this->size.height, hWnd, (HMENU)this->id, Inst, NULL)
		:
		newElem(this->type.c_str(), this->value.c_str(), style, this->pos.x, this->pos.y, this->size.width, this->size.height, hWnd, lol, Inst, NULL);
}

Form_Object::Form_Object(SizePos ownerSize, HWND hWnd, HINSTANCE Inst, int id, string type, string name, string value, int x, int y, int width, int height)
{
	this->id = id;
	this->type = type;
	this->name = name;
	this->value = value;

	this->Calc_Size(width, height, ownerSize);
	this->Calc_Pos(x, y, ownerSize);

	bool createType = (type == "EDIT") ? true : false;

	/*
	showMessage(NULL, "DATA", ((string)"type = " + type + (string)"; name = " + name + (string)"; x = " + std::to_string(this->pos.x) + (string)"; y = " +
		std::to_string(this->pos.y) + (string)"; width = " + std::to_string(this->size.width) + (string)"; height = " + std::to_string(this->size.height)).c_str(), MB_OK);
	*/

	this->hWnd = this->Create_Elem(hWnd, Inst, createType);
}

HWND Form_Object::get_HWND() const
{
	return this->hWnd;
}

int Form_Object::get_ID() const
{
	return this->id;
}

string Form_Object::get_Name() const
{
	return this->name;
}

SizePos Form_Object::get_Size() const
{
	return this->size;
}

Form::Form(HINSTANCE hInstance, int nCmdShow, string FRM, string FRM_TYPE, string FRM_CAPTION, HICON Icon, NOTIFYICONDATA& TrayIcon)
{
	WNDCLASS wc;
	wc.hInstance = hInstance; 
	wc.lpszClassName = _T("FORM");
	wc.lpfnWndProc = Form::WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = Icon; 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;   
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0;  

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	if (!RegisterClass(&wc))
		return;

	this->Objects.push_back(
		FormObj(appProps().windowSize, HWND_DESKTOP, hInstance, this->Objects.size(), FRM, FRM_TYPE, FRM_CAPTION, _FORM_ALIGN_CENTER, _FORM_ALIGN_CENTER, 50, 50)
	);
	this->hWnd = this->Objects[0].get_HWND();

	ShowWindow(this->hWnd, nCmdShow);

	TrayIcon.cbSize = sizeof(NOTIFYICONDATA);
	TrayIcon.hWnd = this->hWnd;
	TrayIcon.uVersion = NOTIFYICON_VERSION;
	TrayIcon.uCallbackMessage = WM_USER;
	TrayIcon.hIcon = Icon;
	TrayIcon.uFlags = NIF_MESSAGE | NIF_ICON;
	Shell_NotifyIcon(NIM_ADD, &TrayIcon);

	MSG msg;
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
	BOOL bRet = 0;
	while (bRet = GetMessage(&msg, nullptr, 0, 0))
	{
		if (-1 == bRet) 
			break;

		if (!TranslateAccelerator(this->hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

string Form::get_ObjectNameByParamW(WPARAM p) const
{
	size_t i;
	int param = LOWORD(p);
	for (i = 0; i < this->Objects.size(); i++)
		if (this->Objects[i].get_ID() == param)
			return this->Objects[i].get_Name();

	return "";
}

FormObj Form::get_ObjectByParamW(WPARAM p) const
{
	size_t i;
	int param = LOWORD(p);
	for (i = 0; i < this->Objects.size(); i++)
		if (this->Objects[i].get_ID() == param)
			return this->Objects[i];

	return this->Objects[0];
}

FormObj Form::get_ObjectByName(string n) const
{
	size_t i;
	for (i = 0; i < this->Objects.size(); i++)
		if (this->Objects[i].get_Name() == n)
			return this->Objects[i];

	return this->Objects[0];
}

LRESULT CALLBACK Form::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		case WM_COMMAND:
		case WM_DESTROY:
		case WM_CLOSE:
			break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);

			break;
		}

		case WM_QUERYENDSESSION:
		{
			PostQuitMessage(0);

			break;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
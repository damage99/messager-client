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
	this->pos.x = (x == Form::ALIGN_CENTER) ? utils::getCenter(ownerSize.width, this->size.width) : utils::getPercents(ownerSize.width, x);
	this->pos.y = (y == Form::ALIGN_CENTER) ? utils::getCenter(ownerSize.height, this->size.height) : utils::getPercents(ownerSize.height, y);

	return (void)0;
}

Form_Object::Form_Object(int id, string type, string name, string value, int x, int y, int width, int height, SizePos ownerSize)
{
	this->id = id;
	this->type = type;
	this->name = name;
	this->caption = value;

	this->Calc_Size(width, height, ownerSize);
	this->Calc_Pos(x, y, ownerSize);
}

Form::Form(HINSTANCE hInstance, string FRM, int iconResourceID)
{
	this->Icon = LoadIcon(hInstance, MAKEINTRESOURCEW(iconResourceID));

	WNDCLASS wc;
	wc.hInstance = hInstance;
	wc.lpszClassName = _T("FORM");//std::wstring(FRM.begin(), FRM.end()).c_str();
	wc.lpfnWndProc = Form::WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = this->Icon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	if (!RegisterClass(&wc))
		return;

	Form_Object frmObject(1, FRM, "", "", Form::ALIGN_CENTER, Form::ALIGN_CENTER, 50, 50, appProps().windowSize);
	newElem(frmObject.getType().c_str(), frmObject.getCaption().c_str(), WS_POPUP, frmObject.getPos().x, frmObject.getPos().y, frmObject.getSize().width, frmObject.getSize().height, HWND_DESKTOP, nullptr, hInstance, this);
}

LRESULT CALLBACK Form::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Form* self;
	if (message == WM_NCCREATE) 
	{
		self = reinterpret_cast<Form*>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);
		self->hWnd = hWnd;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(self));
	}
	else 
		self = reinterpret_cast<Form*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
		case WM_COMMAND:
		case WM_DESTROY:
		case WM_CLOSE:
			break;

		case WM_CREATE:
			return self->ON_CREATE(hWnd, message);

		case WM_PAINT:
			return self->ON_PAINT(hWnd, message);

		case WM_QUERYENDSESSION:
			return self->ON_QUERYENDSESSION(hWnd, message);

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return Form::CALLBACK_RET_DEFAULT;
}
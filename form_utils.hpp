#pragma once
#include "includes.hpp"

enum FORM_CALLBACK_RET
{
	_DEFAULT
};

enum FORM_ALIGN
{
	_CENTER
};

using std::string;

typedef struct Object_SizePosition
{
	union
	{
		int x;
		int width;
	};
	union
	{
		int y;
		int height;
	};
} SizePos;

typedef struct Application_Properties
{
	public:
		Application_Properties();

		SizePos windowSize;
} appProps;

typedef struct Form_Object
{
	public:
		Form_Object(int, string, string, string, int, int, int, int, SizePos);
		string getType() const { return type; }
		string getName() const { return name; }
		string getCaption() const { return caption; }

		SizePos getPos() const { return pos; }
		SizePos getSize() const { return size; }

	private:
		HWND hWnd;
		int id;

		string type;
		string name;
		string caption;

		SizePos pos;
		SizePos size;

		void Calc_Size(int, int, SizePos);
		void Calc_Pos(int, int, SizePos);
} FormObj;

class Form
{
	public:
		Form(HINSTANCE, string, int);
		
		const HWND get_HWND() const { return hWnd; }

		static const FORM_CALLBACK_RET CALLBACK_RET_DEFAULT = _DEFAULT;
		static const FORM_ALIGN ALIGN_CENTER = _CENTER;

	private:
		HWND		hWnd;
		HICON Icon;
		NOTIFYICONDATA TrayIcon;

		LRESULT ON_CREATE(HWND, UINT);
		LRESULT ON_PAINT(HWND, UINT);
		LRESULT ON_QUERYENDSESSION(HWND, UINT);

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};
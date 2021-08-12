#pragma once
#include "includes.hpp"

#define _FORM_ALIGN_CENTER -1

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
		Form_Object(SizePos, HWND, HINSTANCE, int, string, string, string, int, int, int, int);
	
		HWND get_HWND() const;
		int get_ID() const;
		string get_Name() const;
		SizePos get_Size() const;

	private:
		HWND hWnd;
		int id;

		string type;
		string name;
		string value;

		SizePos pos;
		SizePos size;

		void Calc_Size(int, int, SizePos);
		void Calc_Pos(int, int, SizePos);

		HWND Create_Elem(HWND, HINSTANCE, bool);

} FormObj;

class Form
{
	public:
		Form(HINSTANCE, int, string, string, string, HICON, NOTIFYICONDATA &);

	private:
		HWND		hWnd;

		std::vector<FormObj> Objects;

		string get_ObjectNameByParamW(WPARAM) const;
		FormObj get_ObjectByParamW(WPARAM) const;
		FormObj get_ObjectByName(string) const;

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};
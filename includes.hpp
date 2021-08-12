#ifndef _INCLUDES_
#define _INCLUDES_

#include "targetver.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <shellapi.h>
#include <vector>

#include "messager.hpp"
#include "utils.hpp"

#define showMessage(hWnd, head, text, buttons) MessageBoxA(hWnd, text, head, buttons)

#define newElem CreateWindowA
#define extendElem CreateWindowExA

#define IDR_ACCELERATOR 108

#endif

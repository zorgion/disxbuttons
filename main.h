// This file is part of Notepad++ project
// Copyright (C)2003 Don HO <don.h@free.fr>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid
// misunderstandings, we consider an application to constitute a
// "derivative work" for the purpose of this license if it does any of the
// following:
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <tchar.h>

#define    IDM    40000
#define    IDM_FILE    (IDM + 1000)
#define IDM_FILE_NEW  (IDM_FILE + 1)
#define NPPMSG  (WM_USER + 1000)
#define NPPM_MENUCOMMAND (NPPMSG + 48)
#define NPPM_GETCURRENTSCINTILLA (NPPMSG + 4)

#define SCI_SETTEXT	2181

const int nbFunc = 1;
const int nbChar = 64;

typedef const TCHAR * (__cdecl * PFUNCGETNAME)();
typedef void(__cdecl * PFUNCPLUGINCMD)();

struct NppData
{
	HWND _nppHandle;
	HWND _scintillaMainHandle;
	HWND _scintillaSecondHandle;
};

struct ShortcutKey
{
	bool _isCtrl;
	bool _isAlt;
	bool _isShift;
	UCHAR _key;
};

struct FuncItem
{
	TCHAR _itemName[nbChar];
	PFUNCPLUGINCMD _pFunc;
	int _cmdID;
	bool _init2Check;
	ShortcutKey *_pShKey;
};

extern FuncItem funcItem[nbFunc];
extern NppData nppData;

struct Sci_NotifyHeader {
	HWND hwndFrom;
	ULONG_PTR idFrom;
	unsigned int code;
};

struct SCNotification {
	struct Sci_NotifyHeader nmhdr;
	int position;
	int ch;
	int modifiers;
	int modificationType;
	const char *text;
	int length;
	int linesAdded;
	int message;
	ULONG_PTR wParam;
	LONG_PTR lParam;
	int line;
	int foldLevelNow;	
	int foldLevelPrev;
	int margin;
	int listType;
	int x;
	int y;
	int token;
	int annotationLinesAdded;
	int updated;
};

typedef FuncItem * (__cdecl * PFUNCGETFUNCSARRAY)(int *);

typedef void(__cdecl * PFUNCSETINFO)(NppData);
typedef LRESULT(__cdecl * PMESSAGEPROC)(UINT Message, WPARAM wParam, LPARAM lParam);
typedef void(__cdecl * PBENOTIFIED)(SCNotification *);

extern "C" __declspec(dllexport) void setInfo(NppData);
extern "C" __declspec(dllexport) const TCHAR * getName();
extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *);
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam);
extern "C" __declspec(dllexport) BOOL isUnicode();
extern "C" __declspec(dllexport) void beNotified(SCNotification *);

#endif
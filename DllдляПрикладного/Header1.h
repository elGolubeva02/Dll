#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
int ClipboardInputText(LPWSTR buffer)//записать строку в системный буфер
{
	DWORD len;
	HANDLE hMenu;
	len = wcslen(buffer) + 1;
	hMenu = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));
	memcpy(GlobalLock(hMenu), buffer, len * sizeof(LPWSTR));
	GlobalUnlock(hMenu);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMenu);
	CloseClipboard();
	return 0;
}

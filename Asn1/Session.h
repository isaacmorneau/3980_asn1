#pragma once
#include <Windows.h>
#include <string>

static LPCSTR CommNames[] = { "COM1", "COM2", "COM3", "COM4" };

class Session {
public:
	Session();
	~Session();
	HANDLE getCommHandle();
	bool setSession(int, HWND hwnd);
private:
	HANDLE hComm = INVALID_HANDLE_VALUE;
	int current_Com = 3;
	COMMCONFIG cc;
};
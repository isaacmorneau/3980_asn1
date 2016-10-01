#pragma once
#include <Windows.h>
#include <string>

static LPCSTR CommNames[] = { "COM5","COM5","COM5","COM5","COM5" };//{ "COM1", "COM2", "COM3", "COM4", "COM5", "COM6" };

class Session {
public:
	Session();
	~Session();
	HANDLE getCommHandle();
	bool setSession(int, HWND hwnd);
private:
	HANDLE hComm = INVALID_HANDLE_VALUE;
	int current_Com = -1;
	COMMCONFIG cc;
};
#pragma once
#include <Windows.h>
#include <string>

static LPCSTR CommNames[] = {
	"COM1",
	"COM2",
	"COM3",
	"COM4",
	"COM5",
	"COM6"
};

class Session {
public:
	Session();
	~Session();
	HANDLE getCommHandle();
	bool comIsValid() {return this->hComm != INVALID_HANDLE_VALUE;}
	bool setSession(int);
private:
	HANDLE hComm = INVALID_HANDLE_VALUE;
	int current_Com = -1;
	COMMCONFIG cc;
	COMMTIMEOUTS timeouts;
};
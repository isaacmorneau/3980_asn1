#pragma once
#include <Windows.h>
#include <string>
class Session {
public:
	Session();
	~Session();
	HANDLE *getCommHandle();
	bool setSession(LPCSTR);
private:
	HANDLE hComm;
	LPCSTR current_Com = "";
};
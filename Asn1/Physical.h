#pragma once
#include <Windows.h>
#include <string>
#include "Session.h"
class Physical {
public:
	Physical();
	~Physical();
	void read(Session *, void (*displayChar)(char));
	void stopRead();
	void write(Session *,char);
private:
	static DWORD WINAPI readThread(LPVOID);
	HANDLE hThread = NULL;
	bool threadRunning = false;
};

typedef struct {
	HANDLE hComm;
	void (*displayChar)(char);
} readStruct;
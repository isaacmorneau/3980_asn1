#pragma once
#include <Windows.h>
#include <string>
#include "Session.h"

//debug
#include <string>

#define BUFFSIZE 10

class Physical {
public:
	Physical();
	~Physical();
	void read(Session *, void (*displayChar)(char*));
	void stopRead();
	void write(Session *,char);
private:
	static DWORD WINAPI readThread(LPVOID);
	HANDLE hThread = NULL;
	bool threadRunning = false;
	OVERLAPPED overlap = { 0 };
};

typedef struct {
	HANDLE hComm;
	void (*displayChar)(char*);
	LPOVERLAPPED overlap;
} readStruct;
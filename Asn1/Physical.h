#pragma once
#include <Windows.h>
#include <string>
#include "Session.h"
class Physical {
public:
	Physical();
	~Physical();
	//read creates thread
	void read(Session *, void (*displayChar)(char));
	void stopRead();
	void write(Session *,char);
private:
	//thread function
	static DWORD WINAPI readThread(LPVOID);
	//for thread id
	LPDWORD hReadThreadId = 0;
	//for create thread handle for future termination
	HANDLE hThread = NULL;
	
	bool threadRunning = false;
};

typedef struct {
	HANDLE* hComm;
	void (*displayChar)(char);
} readStruct;
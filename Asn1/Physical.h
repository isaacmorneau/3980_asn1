#pragma once
#include <Windows.h>
#include <string>
class Physical {
public:
	Physical();
	~Physical();
	//read creates thread
	void read();
	char getBuffer();
	char write(char);
private:
	//thread function
	static DWORD WINAPI readThread(LPVOID);
	//for thread id
	LPDWORD hReadThreadId;
	//for com port handle
	HANDLE hComm;
	//for create thread handle
	HANDLE hThread;
	
	char displayBuff = '0';
};


#pragma once
#include <Windows.h>
#include <string>
#define CBUFF char
class Physical {
public:
	Physical(HANDLE*,HWND*);
	~Physical();
	//read creates thread
	void read();
	char getBuffer();
	void write(char);
private:
	//thread function
	static DWORD WINAPI readThread(LPVOID);
	//for thread id
	LPDWORD hReadThreadId;
	//for com port handle
	HANDLE* hComm;
	//for window handle
	HWND* hwnd;
	//for create thread handle
	HANDLE hThread;
	
	//character to read from for the paint event
	//todo make it a queue of some sort
	CBUFF displayBuff = '0';
};

typedef struct {
	HANDLE* hComm;
	CBUFF* cBuff;
	HWND* hwnd;
} readStruct;
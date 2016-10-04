/*
-- SOURCE FILE: Physical.cpp
--
-- PROGRAM: Simple COMM Shell
--
-- FUNCTIONS: 
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- NOTES:
*/
#pragma once
#include <Windows.h>
#include <string>
#include "Session.h"

#define BUFFSIZE 10

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

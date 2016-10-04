/*
-- SOURCE FILE: Session.cpp
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

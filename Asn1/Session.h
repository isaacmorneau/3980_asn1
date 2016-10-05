/*
-- SOURCE FILE: Session.cpp
--
-- PROGRAM: Simple COMM Shell
--
-- CLASS: Session
--
-- FUNCTIONS:
--      HANDLE getCommHandle(void)
--      bool comIsValid(void)
--      bool setSession(int)
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
-- The Session class is build with the OSI model in mind and functions as the
-- class that manages the configuration of COM ports and the current COM
-- connection.
*/
/*
-- FUNCTION: getCommHandle
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: HANDLE getCommHandle(void)
--
-- RETURN: HANDLE the current COM port handle or INVALID_HANDLE_VALUE if the COM
-- port is not set.
--
-- NOTES:
-- Gets the COM port for the current session. The default value if no COM port
-- is selected is INVALID_HANDLE_VALUE.
*/
/*
-- FUNCTION: comIsValid
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: bool comIsValid(void)
--
-- RETURN: bool checks if the current comport is valid and usable.
--
-- NOTES:
-- Checks the current Session COM handle against INVALID_HANDLE_VALUE to verify
-- its set.
*/
/*
-- FUNCTION: setSession
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: bool setSession(int comNumber)
--      comNumber the zero based number of the com port to use
--          ie 0 is COM1
-- RETURN: bool returns true if the session was set successfully and false if it
-- failed.
--
-- NOTES:
-- Upon failure there a message box is displayed with the reason for failure
-- described.
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

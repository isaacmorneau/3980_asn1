/*
-- SOURCE FILE: Physical.cpp
--
-- PROGRAM: Simple COMM Shell
--
-- CLASS: Pysical
--
-- FUNCTIONS:
--      void read(Session*, void (*displayChar)(char))
--      void stopRead(void)
--      void write(Session*, char)
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
-- The Physical class is build with the OSI model in mind and functions as the
-- class that handles all direct interaction with the COM ports. The Physical
-- class also manages an internal thread for reading all incoming characters.
-- This thread is invoked by the menu option 'Start' and can be killed by stop
-- or by closing the program.
*/
/*
-- FUNCTION: read
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: void read(Session*, void (*displayChar)(char))
--      Session* The main Session object
--      void (*displayChar)(char) A function that will handle characters as they
--                                  are read in.
--
-- RETURN: void.
--
-- NOTES:
-- Accepts the current session and a function pointer to what will handle the
-- characters as they are read from the COM port. Return is void so on error
-- a message box is displayed relaying what needs to be changed, such as no COM
-- port selected.
--
*/
/*
-- FUNCTION: stopRead
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: void stopRead(void)
--
-- RETURN: void.
--
-- NOTES:
-- Kills the read thread if there is one.
*/
/*
-- FUNCTION: write
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: void write(Session*, char)
--
-- RETURN: void.
--
-- NOTES:
-- Writes the character passed in to the current COM in Session if one is
-- selected, Otherwise, a message box is displayed relaying what needs to be
-- changed, such as  such as no COM port selected.
*/

#pragma once
#include <Windows.h>
#include <string>
#include "Session.h"

#define BUFFSIZE 10

class Physical {
public:
    ~Physical();
    void read(Session *, void (*displayChar)(char));
    void stopRead();
    void write(Session *,char);
private:
    static DWORD WINAPI readThread(LPVOID);
    HANDLE hThread = NULL;
    bool threadRunning = false;
};


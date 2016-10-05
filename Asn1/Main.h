/*
-- SOURCE FILE: Main.cpp
--
-- PROGRAM: Simple COMM Shell
--
-- FUNCTIONS:
--                LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM)
--                void drawChar(char c)
--                int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
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
-- The program provides a "Dumb" terminal emulator that transmits all characters
-- entered into the window over a serial port and prints all characters read to
-- the window.
--
-- Upon opening the window the screen is blank with three menu options:
--  Settings, Run, Stop, and Exit.
--     Settings:
--      provides a dropdown to select a port from COM1-COM6. When a port is
--      selected a port configuration window is shown and when configuration is
--      saved. Upon successful configuration that COM port is set to current.
--
--     Run
--      Starts a listening thread on the current COM port if there isnt one
--      already. This thread will read all characters recieved and display them
--      until Stop or Exit is called.
--
--     Stop
--      Kills the current listining thread if there is one.
--
--     Exit
--      Kills all threads, closes handle to COM port and exits the program.
*/
/*
-- FUNCTION: WndProc
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM)
--      HWND The handle to the window.
--      UINT The message to be handled.
--      WPARAM Additional information about the message.
--      LPARAM Additional information about the message.
--
-- RETURN: LRESULT the result of the message processing and depends on the
-- message sent.
--
-- NOTES:
-- This is the callback for all window events and as such handles the menu
-- selections and killing the threads on menu changes.
-- For more info:
--https://msdn.microsoft.com/en-us/library/windows/desktop/ms633573(v=vs.85).aspx
*/
/*
-- FUNCTION: drawChar
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: void drawChar(char c)
--      char c The character to be drawn to the console
--
-- RETURN: void.
--
-- NOTES:
-- drawChar accepts a character (Usually from the read thread in Physical) and
-- renders it on the screen. Using static declarations, the function also
-- manages the position for the next character to be written.
*/
/*
-- FUNCTION: WinMain
--
-- DATE: October 1st, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Isaac Morneau; A00958405
--
-- PROGRAMMER: Isaac Morneau; A00958405
--
-- INTERFACE: int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
--          HINSTANCE A handle to the current instance of the application.
--          HINSTANCE A handle to the previous instance of the application.
--          LPSTR The command line for the application, minus the program name.
--          int Controls how the window is to be shown
--
-- RETURN: int the return code for the entire program.
--
-- NOTES:
-- Entry point for the program. It creates and registers all windows and window
-- classes as well as the Physical and Session layer objects.
-- For more info:
-- https://msdn.microsoft.com/en-us/library/windows/desktop/ms633559(v=vs.85).aspx
*/


#pragma once
#define STRICT

#include <windows.h>
#include <stdio.h>
#include "menu.h"
#include "Physical.h"
#include "Session.h"

char Name[] = "Assignment 1 Comm Shell";
char str[80] = "";//output buffer

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//filewide window handle to allow drawCharacter
//which is to be passed into the read thread.
HWND drawHwnd = 0;

Physical *phs;
Session *sesh;

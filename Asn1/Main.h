/*
-- SOURCE FILE: Main.cpp
--
-- PROGRAM: Simple COMM Shell
--
-- FUNCTIONS: 
--				LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
--				void drawChar(char c)
--				int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
--					LPSTR lspszCmdParam, int nCmdShow)
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
//to be passed into the read thread.
HWND drawHwnd = 0;

Physical *phs;
Session *sesh;

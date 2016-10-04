// Program WinMenu.cpp
#define STRICT

#include <windows.h>
#include <stdio.h>
#include "menu.h"
#include "Physical.h"
#include "Session.h"

char Name[] = "Assignment 1 Comm Shell";
char str[80] = "";//output buffer

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//filewide window handle to allow function encapsulation
HWND drawHwnd = 0;

Physical *phs;
Session *sesh;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
	LPSTR lspszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASSEX Wcl;
	{
		Wcl.cbSize = sizeof(WNDCLASSEX);
		Wcl.style = CS_HREDRAW | CS_VREDRAW;
		Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
		Wcl.hIconSm = NULL; // use small version of large icon
		Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style

		Wcl.lpfnWndProc = WndProc;
		Wcl.hInstance = hInst;
		Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //white background
		Wcl.lpszClassName = Name;

		Wcl.lpszMenuName = "MYMENU"; // The menu Class
		Wcl.cbClsExtra = 0;      // no extra memory needed
		Wcl.cbWndExtra = 0;
	}
	if (!RegisterClassEx(&Wcl))
		return 0;

	hwnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, 10, 10,
		800, 400, NULL, NULL, hInst, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	//level inits(make sure its before the message loop...)
	phs = new Physical();
	sesh = new Session();

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

void drawChar(char c) {
	static unsigned x = 0;
	static unsigned y = 0;
	static HDC hdc;
	if (x == 79) {//width / 10 - 1
		y++;
		x = 0;
	}
	hdc = GetDC(drawHwnd);
	sprintf_s(str, "%c", c);
	TextOut(hdc, 10 * x++, 20 * y, str, strlen(str));
	ReleaseDC(drawHwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT paintstruct;
	if(!drawHwnd)
		drawHwnd = hwnd;
	switch (Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_COM1:
			sesh->setSession(0);
			break;
		case IDM_COM2:
			sesh->setSession(1);
			break; 
		case IDM_COM3:
			sesh->setSession(2);
			break;
		case IDM_COM4:
			sesh->setSession(3);
			break;
		case IDM_COM5:
			sesh->setSession(4);
			break;
		case IDM_COM6:
			sesh->setSession(5);
			break;
		case IDM_RUN:
			phs->read(sesh, drawChar);
			break;
		case IDM_STOP:
			phs->stopRead();
			break;
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CHAR:
		phs->write(sesh,(char)wParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &paintstruct);
		TextOut(hdc, 0, 0, str, strlen(str));
		EndPaint(hwnd, &paintstruct);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
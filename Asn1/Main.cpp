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

//the different com file names
LPCSTR	lpszCommName[] = { "COM1", "COM2", "COM3", "COM4" };

COMMCONFIG	cc;

//stored in session
//HANDLE hComm;
//filewide window handle to allow agregate functions
HWND drawHwnd;

//Physical layer object
Physical *phs;
//Session layer object
Session *sesh;

//keep track of current port
int current_Com_Port = 3;

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
		600, 400, NULL, NULL, hInst, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//set the cc params
	cc.dwSize = sizeof(COMMCONFIG);
	cc.wVersion = 0x100;

	//level inits(make sure its before the message loop...)
	phs = new Physical();
	sesh = new Session();

	//default to 4th port
	if (!sesh->setSession(lpszCommName[current_Com_Port]))
	{
		MessageBox(NULL, "Error opening COM port:", lpszCommName[current_Com_Port], MB_OK);
		return FALSE;
	}
	

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

void drawChar(char c) {
	static unsigned p = 0;
	static HDC hdc;
	hdc = GetDC(drawHwnd);
	sprintf_s(str, "%c", c);
	TextOut(hdc, 10 * p++, 0, str, strlen(str));
	ReleaseDC(drawHwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paintstruct;
	drawHwnd = hwnd;

	switch (Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_COM1:
			current_Com_Port = 0; 
			sesh->setSession(lpszCommName[current_Com_Port]);
			GetCommConfig(sesh->getCommHandle(), &cc, &cc.dwSize);
			if (!CommConfigDialog(lpszCommName[current_Com_Port], hwnd, &cc))
				break;
			break;
		case IDM_COM2:
			current_Com_Port = 1;
			sesh->setSession(lpszCommName[current_Com_Port]);
			GetCommConfig(sesh->getCommHandle(), &cc, &cc.dwSize);
			if (!CommConfigDialog(lpszCommName[current_Com_Port], hwnd, &cc))
				break;
			break; 
		case IDM_COM3:
			current_Com_Port = 2;
			sesh->setSession(lpszCommName[current_Com_Port]);
			GetCommConfig(sesh->getCommHandle(), &cc, &cc.dwSize);
			if (!CommConfigDialog(lpszCommName[current_Com_Port], hwnd, &cc))
				break;
			break;
		case IDM_COM4:
			current_Com_Port = 3;
			sesh->setSession(lpszCommName[current_Com_Port]);
			GetCommConfig(sesh->getCommHandle(), &cc, &cc.dwSize);
			if (!CommConfigDialog(lpszCommName[current_Com_Port], hwnd, &cc))
				break;
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
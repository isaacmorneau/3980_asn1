// Program WinMenu.cpp

#define STRICT

#include <windows.h>
#include <stdio.h>
#include "menu.h"
#include "Physical.h"

char Name[] = "Assignment 1 Comm Shell";
char str[80] = "";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#pragma warning (disable: 4096)

//the different com file name
LPCSTR	lpszCommName;
LPCSTR	lpszCommName_1 = "com1";
LPCSTR	lpszCommName_2 = "com2";
LPCSTR	lpszCommName_3 = "com3";
COMMCONFIG	cc;
HANDLE hComm;

//Physical layer object
Physical *phs = new Physical();


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

	//set it to the third com port
	lpszCommName = lpszCommName_3;
	if ((hComm = CreateFile(lpszCommName, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL))
		== INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Error opening COM port:", "", MB_OK);
		return FALSE;
	}

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	int response;
	HDC hdc;
	PAINTSTRUCT paintstruct;
	static unsigned k = 0;

	switch (Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_COM1:
			cc.dwSize = sizeof(COMMCONFIG);
			cc.wVersion = 0x100;
			GetCommConfig(hComm, &cc, &cc.dwSize);
			if (!CommConfigDialog(lpszCommName, hwnd, &cc))
				break;
			break;
		case IDM_COM2:
			cc.dwSize = sizeof(COMMCONFIG);
			cc.wVersion = 0x100;
			GetCommConfig(hComm, &cc, &cc.dwSize);
			if (!CommConfigDialog(lpszCommName, hwnd, &cc))
				break;
			break; 
		case IDM_COM3:
			cc.dwSize = sizeof(COMMCONFIG);
			cc.wVersion = 0x100;
			GetCommConfig(hComm, &cc, &cc.dwSize);
			if (!CommConfigDialog(lpszCommName, hwnd, &cc))
				break;
			break;
		case IDM_RUN:
			phs->read();
			break;
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CHAR:// Process keystroke
		hdc = GetDC(hwnd);// get device context
		sprintf_s(str, "%c", (char)wParam);// Convert char to string
		TextOut(hdc, 10 * k, 0, str, strlen(str));// output character	
		k++;// increment the screen x-coordinate
		ReleaseDC(hwnd, hdc);// Release device context
		break;

	case WM_PAINT:		// Process a repaint message
		hdc = BeginPaint(hwnd, &paintstruct); // Acquire DC
		TextOut(hdc, 0, 0, str, strlen(str)); // output character
		EndPaint(hwnd, &paintstruct); // Release DC
		break;

	case WM_DESTROY:	// Terminate program
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
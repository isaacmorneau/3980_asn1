#include "Physical.h"

Physical::Physical(HANDLE* comm, HWND* window) {
	this->hComm = comm;
	this->hwnd = window;
	return;
}
Physical::~Physical() {
	return;
}
char Physical::getBuffer() {
	return this->displayBuff;
}
void Physical::read() {
	readStruct* rst = new readStruct;
	rst->hComm = this->hComm;
	rst->cBuff = &this->displayBuff;
	rst->hwnd = this->hwnd;

	this->hThread = CreateThread(NULL, 0, Physical::readThread, (LPVOID)(rst), 0, this->hReadThreadId);
	if (this->hThread) {
		//it was create yay
	}
}
DWORD WINAPI Physical::readThread(LPVOID n) {
	readStruct *c = (readStruct*)n;//the buffer in the physical object
	LPDWORD acRead = 0;
	HDC hdc;
	char str[80];
	unsigned int xpos = 0;
	while (1) {
		ReadFile(c->hComm, c->cBuff, 1, acRead, NULL);
		if (acRead > 0) {
			hdc = GetDC(*c->hwnd);// get device context
			sprintf_s(str, "%c", *c->cBuff);// Convert char to string
			TextOut(hdc,10*xpos++, 0, str, strlen(str));// output character	
			ReleaseDC(*c->hwnd, hdc);// Release device context
		}
	}
	return 0;
}

void Physical::write(char){
	return;
}


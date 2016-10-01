#include "Physical.h"

Physical::Physical() {
	return;
}
Physical::~Physical() {
	return;
}
void Physical::read(Session* s, void (*displayChar)(char*)) {
	HANDLE com = s->getCommHandle();
	if (com == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, "No COMM port selected.", "Operation Denied", MB_OK);
		return;
	}
	readStruct* rst = new readStruct;
	rst->hComm = com;
	rst->displayChar = displayChar;
	//rst->overlap = &this->overlap;

	LPDWORD hReadThreadId = 0;

	if (!this->threadRunning)
		this->hThread = CreateThread(NULL, 0, Physical::readThread, (LPVOID)(rst), 0, hReadThreadId);
	else
		MessageBox(NULL, "Read thread already running.", "Operation Denied", MB_OK);

	if (this->hThread)
		this->threadRunning = true;
}

DWORD WINAPI Physical::readThread(LPVOID n) {
	readStruct *c = (readStruct*)n;
	DWORD acRead = 0;
	char buff [BUFFSIZE] = "";
	while (1) {
		ReadFile(c->hComm, &buff, BUFFSIZE, &acRead, NULL);
		if (acRead > 0) {
			c->displayChar(buff);
		}
	}
	return 0;
}

void Physical::stopRead() {
	if (this->threadRunning && TerminateThread(this->hThread, 0))
		this->threadRunning = false;
}

void Physical::write(Session *s,char c){
	HANDLE comm = s->getCommHandle();
	DWORD written = 0;
	WriteFile(comm, &c, 1, &written, NULL);
	return;
}


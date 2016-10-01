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
	rst->overlap = &this->overlap;

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
	DWORD acRead;
	DWORD dwCommEvent;
	char buff [BUFFSIZE];
	//creepy

	while (1) {
		if (WaitCommEvent(c->hComm, &dwCommEvent, NULL)) {
			if (ReadFile(c->hComm, buff, 1, &acRead, NULL))
				c->displayChar(buff);// A byte has been read; process it.
			else
				return 1;// An error occurred in the ReadFile call.
			break;
		} else {
			//return 2;// Error in WaitCommEvent.
		}
	}
	return 3;
}

void Physical::stopRead() {
	if (this->threadRunning && TerminateThread(this->hThread, 0))
		this->threadRunning = false;
}

void Physical::write(Session *s,char c){
	HANDLE comm = s->getCommHandle();
	DWORD written = 0;
	WriteFile(comm, &c, 1, &written, &this->overlap);
	return;
}


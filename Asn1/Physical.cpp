#include "Physical.h"

Physical::Physical() {
	return;
}
Physical::~Physical() {
	return;
}
void Physical::read(Session* s, void (*displayChar)(char)) {
	readStruct* rst = new readStruct;
	rst->hComm = s->getCommHandle();
	rst->displayChar = displayChar;
	if (!this->threadRunning)
		this->hThread = CreateThread(NULL, 0, Physical::readThread, (LPVOID)(rst), 0, this->hReadThreadId);
	else
		MessageBox(NULL, "Read thread already running.", "Operation Denied", MB_OK);
	if (this->hThread)
		//it was created
		this->threadRunning = true;
}

DWORD WINAPI Physical::readThread(LPVOID n) {
	readStruct *c = (readStruct*)n;//the buffer in the physical object
	LPDWORD acRead = 0;
	char buff;
	while (1) {
		//read _a_ char
		ReadFile(c->hComm, &buff, 1, acRead, NULL);
		if (acRead > 0) 
			c->displayChar(buff);
	}
	return 0;
}

void Physical::stopRead() {
	//kill the read thread if its running
	if (this->threadRunning && TerminateThread(this->hThread, 0))
		//sucessfully killed it.
		this->threadRunning = false;
}

void Physical::write(Session *s,char c){
	HANDLE comm = *s->getCommHandle();
	LPDWORD written = 0;
	WriteFile(comm, &c, 1, written, 0);
	return;
}


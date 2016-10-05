#include "Physical.h"

//only used internally to pass handle and function to thread
typedef struct {
    HANDLE hComm;
    void(*displayChar)(char);
} readStruct;
Physical::~Physical() {
    this->stopRead();
    return;
}
void Physical::read(Session* s, void (*displayChar)(char)) {
    HANDLE com = s->getCommHandle();
    if (!s->comIsValid()) {
        MessageBox(NULL, "No COMM port selected.", "Operation Denied", MB_OK);
        return;
    }
    readStruct* rst = new readStruct;
    rst->hComm = com;
    rst->displayChar = displayChar;

    DWORD hReadThreadId = 0;

    if (!this->threadRunning)
        this->hThread = CreateThread(NULL, 0, Physical::readThread, (LPVOID)(rst), 0, &hReadThreadId);
    else
        MessageBox(NULL, "Read thread already running.", "Operation Denied", MB_OK);

    if (this->hThread)
        this->threadRunning = true;
}

DWORD WINAPI Physical::readThread(LPVOID n) {
    readStruct *c = (readStruct*)n;
    DWORD acRead;
    char buff;

    while (1) {
        if (ReadFile(c->hComm, &buff, 1, &acRead, NULL) && acRead > 0)
            c->displayChar(buff);
    }
    return 1;
}

void Physical::stopRead() {
    if (this->threadRunning && TerminateThread(this->hThread, 0))
        this->threadRunning = false;
}

void Physical::write(Session *s,char c){
    HANDLE comm = s->getCommHandle();
    if (!s->comIsValid()) {
        MessageBox(NULL, "No COMM port selected.", "Operation Denied", MB_OK);
        return;
    }
    DWORD written = 0;
    WriteFile(comm, &c, 1, &written, NULL);
    return;
}


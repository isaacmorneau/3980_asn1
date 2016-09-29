#include "Physical.h"

Physical::Physical() {
	return;
}
Physical::~Physical() {
	return;
}
char Physical::getBuffer() {
	return this->displayBuff;
}
void Physical::read() {
	this->hThread = CreateThread(NULL, 0, Physical::readThread, (LPVOID)(&this->displayBuff), 0, this->hReadThreadId);
	if (this->hThread) {
		//it was create yay
	}
}
DWORD WINAPI Physical::readThread(LPVOID n) {
	char *c = (char*)n;
	*c = '!';
	return 0;
}

char Physical::write(char){
	return 0;
}


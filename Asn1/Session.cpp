#include "Session.h"

Session::Session() {
	this->cc.dwSize = sizeof(COMMCONFIG);
	this->cc.wVersion = 0x100;

	this->timeouts = { 0 };
	this->timeouts.ReadIntervalTimeout = 1;
	this->timeouts.ReadTotalTimeoutMultiplier = 1;
	this->timeouts.ReadTotalTimeoutConstant = 1;
	this->timeouts.WriteTotalTimeoutMultiplier = 1;
	this->timeouts.WriteTotalTimeoutConstant = 1;

	return;
}

Session::~Session() {
	if (this->hComm != INVALID_HANDLE_VALUE)
		CloseHandle(this->hComm);
	return;
}
HANDLE Session::getCommHandle() {
	return this->hComm;
}
bool Session::setSession(int commPort, HWND hwnd) {
	if (this->current_Com == commPort) {
		return true;
	}

	if (this->hComm != INVALID_HANDLE_VALUE)
		CloseHandle(this->hComm);
	this->current_Com = commPort;

	this->hComm = CreateFile(CommNames[this->current_Com], GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH/*FILE_FLAG_OVERLAPPED*/, NULL);
	if(this->hComm == INVALID_HANDLE_VALUE){
		MessageBox(NULL, "Error opening COM port:", CommNames[this->current_Com], MB_OK);
		return false;
	}

	if (!SetCommTimeouts(this->hComm, &this->timeouts)) {
		MessageBox(NULL, "Error opening setting COM Timeouts", CommNames[this->current_Com], MB_OK);
		return false;
	}

	GetCommConfig(this->hComm, &cc, &cc.dwSize);
	CommConfigDialog(CommNames[this->current_Com], hwnd, &cc);

	return true;
}
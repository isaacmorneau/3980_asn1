#include "Session.h"

Session::Session() {
	return;
}

Session::~Session() {
	return;
}
HANDLE *Session::getCommHandle() {
	return &this->hComm;
}
bool Session::setSession(LPCSTR commPortName) {
	if (this->current_Com == "")
		this->current_Com = commPortName;
	else if (this->current_Com == commPortName)
		return true;
	this->hComm = CreateFile(this->current_Com, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if(this->hComm == INVALID_HANDLE_VALUE){
		MessageBox(NULL, "Error opening COM port:", commPortName, MB_OK);
		return false;
	}
	return true;
}
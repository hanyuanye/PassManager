#include "Messenger.h"



Messenger::Messenger()
{
}


Messenger::~Messenger()
{
}

void Messenger::msg(std::string message)
{
	std::cout << message << std::endl;
}

void Messenger::msg(std::vector<std::string> messages)
{
	for (std::string message : messages) {
		std::cout << message << std::endl;
	}
}

void Messenger::storePassword(std::string password)
{
	this->lastPassword = password;
	copyToClipboard();
}

void Messenger::copyToClipboard()
{
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, lastPassword.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), lastPassword.c_str(), lastPassword.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

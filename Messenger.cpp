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

void Messenger::msg(const std::experimental::filesystem::v1::directory_entry & filename)
{
	std::cout << filename << std::endl;
}

void Messenger::msg(std::vector<std::string> messages)
{
	for (std::string message : messages) {
		std::cout << message << std::endl;
	}
}

void Messenger::error(int errorCode)
{
	switch (errorCode) {
	case 0:
		msg("File does not exist.");
		break;
	case 1:
		msg("Command does not exist.");
		break;
	default:
		break;
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

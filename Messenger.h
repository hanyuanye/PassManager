#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
class Messenger
{
public:
	Messenger();
	~Messenger();
	void msg(std::string msg);
	void msg(std::vector<std::string> msgs);
	void storePassword(std::string password);
	void copyToClipboard();
private:
	std::string lastPassword;
};


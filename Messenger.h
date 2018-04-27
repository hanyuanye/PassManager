#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <experimental/filesystem>
class Messenger
{
public:
	Messenger();
	~Messenger();
	void msg(std::string msg);
	void msg(const std::experimental::filesystem::v1::directory_entry& filename);
	void msg(std::vector<std::string> msgs);
	void error(int errorCode);
	void storePassword(std::string password);
	void copyToClipboard();
private:
	std::string lastPassword;
};


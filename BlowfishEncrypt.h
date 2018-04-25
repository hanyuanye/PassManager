#pragma once
#include <string>
class BlowfishEncrypt
{
public:
	BlowfishEncrypt();
	~BlowfishEncrypt();
	std::string encrypt(std::string input);
	std::string decrypt(std::string input);
};


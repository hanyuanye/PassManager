#pragma once
#include <string>
class Encrypt
{
public:
	Encrypt();
	~Encrypt();
	std::string encrypt(std::string input);
	std::string decrypt(std::string input);
private:
	char key[4] = { 'P', 'A', 'F', 'S' };
};


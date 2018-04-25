#include "Encrypt.h"



Encrypt::Encrypt()
{
}


Encrypt::~Encrypt()
{
}


//Simple XOR encryption implemention
std::string Encrypt::encrypt(std::string input)
{
	for (int i = 0; i < input.size(); i++) {
		input[i] = input[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}
	return input;
}

std::string Encrypt::decrypt(std::string input)
{
	return encrypt(input);
}

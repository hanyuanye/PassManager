#include "InputHandler.h"



InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

//Generating a password with random letters and numbers.
std::string InputHandler::generatePassword(int length)
{
	std::string password;
	for (int i = 0; i < length; i++) { 
		char curr = generateRandomCharacter();
		password += curr;
	}
	//Appending ! because some passwords requires symbols.
	password += "!";
	return password;
}

char InputHandler::generateRandomCharacter()
{

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 62);
	int randomResult = distribution(generator);
	int ascii = 0;
	if (randomResult < 10) { //value is from 1 - 10
		ascii = 48 + randomResult;
	}
	else if (randomResult < 36) { // value is an upper case character
		ascii = 65 + randomResult;
	}
	else if (randomResult < 62) { //value is a lower case character
		ascii = 97 + randomResult;
	}
	else if (randomResult == 62) {
		ascii = 33;
	}
	char asciiChar = ascii;
	return asciiChar;
}

bool InputHandler::isEqual(const std::string & a, const std::string & b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

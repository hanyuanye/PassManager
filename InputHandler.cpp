#include "InputHandler.h"



InputHandler::InputHandler()
{
	messenger = std::make_shared<Messenger>();
	database = new Database(messenger);
}


InputHandler::~InputHandler()
{
	delete database;
}

std::string InputHandler::getInput()
{
	messenger->msg(INSTRUCTIONS);
	std::string input;
	std::getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

bool InputHandler::callCommand(std::string input)
{
	std::string command = input.substr(0, input.find(" "));
	if (command == "help") {
		return help();
	}
	if (command == "copy") {
		return copy();
	}
	std::string key = "";
	if (input.find(" ") != std::string::npos) {
		key += input.substr(input.find(" ") + 1, input.size() - 1);
	}
	return database->callCommand(command, key);
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

bool InputHandler::copy()
{
	messenger->copyToClipboard();
	return true;
}

bool InputHandler::help()
{
	std::vector<std::string> commandList = database->commandList;
	commandList.erase(std::find(commandList.begin(), commandList.end(), "verify"));
	commandList.push_back("copy");
	messenger->msg(commandList);
	return true;
}


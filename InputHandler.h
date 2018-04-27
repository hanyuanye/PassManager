#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <map>
#include "Database.h"

#define PASSWORD_LENGTH 15
const std::string INSTRUCTIONS = "Enter commands. Type \"help\" for full command list.";

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	std::string getInput();
	bool callCommand(std::string input);
	std::string generatePassword(int length);
private:
	Database *database;
	char generateRandomCharacter();
	static std::vector<std::string> commandList;
	bool isEqual(const std::string& a, const std::string& b); //Case insensitive equality check
	std::shared_ptr<Messenger> messenger;
	bool copy();
	bool help();
};


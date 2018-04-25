#pragma once
#include <iostream>
#include <random>
#include <vector>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void callDatabase(std::string input, std::string action);
	std::string generatePassword(int length);

private:
	char generateRandomCharacter();
	static std::vector<std::string> commandList;
	bool isEqual(const std::string& a, const std::string& b); //Case insensitive equality check
};


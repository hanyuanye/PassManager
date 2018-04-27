#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <memory>
#include <experimental/filesystem>
#include <map>
#include <random>
#include "picosha2.h"
#include "Encrypt.h"
#include "Messenger.h"

#define ERROR_FILE_DOES_NOT_EXIST 0
#define ERROR_COMMAND_DOES_NOT_EXIST 1
const std::string DIRECTORY = "C:/PassFolder";
const std::string VERIFY_PASSWORD = "verify_password";

class Database
{
public:
	Database(std::shared_ptr<Messenger> messenger);
	~Database();
	const bool callCommand(std::string command, std::string key);
	const bool addGeneratedPassword(std::string key, std::string password);
	bool directoryOpen;
	const static std::vector<std::string> commandList;
private:
	//Command Functions
	bool isVerifiedUser(const std::string &none); //only for function pointer map, string none is not neccessary
	bool addPassword(const std::string &key);
	bool removePassword(const std::string &key);
	bool searchPassword(const std::string &key);
	bool displayPasswordsParentNames(const std::string &none); //only for function pointer map, string none is not neccessary

	//Helper Functions for Command Functions
	bool isFileExist(const std::string &fileName);
	std::string getInput(const std::string &command);
	std::string readFile(const std::string &path);
	std::string createPath(const std::string &fileName);
	std::unique_ptr<Encrypt> encrypter;
	std::shared_ptr<Messenger> messenger;
	std::string getHashedSaltedPassword(const std::string &input, std::string & salt);
};


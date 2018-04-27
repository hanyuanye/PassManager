#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <memory>
#include <experimental/filesystem>
#include <map>
#include "picosha2.h"
#include "Encrypt.h"

const std::string DIRECTORY = "C:/PassFolder";
const std::string VERIFY_PASSWORD = "verify_password";

class Database
{
public:
	Database();
	~Database();
	const bool callCommand(std::string command, std::string key);
	bool isVerifiedUser(const std::string &none); //only for function pointer map, string none is not neccessary
	bool addPassword(const std::string &key);
	bool removePassword(const std::string &key);
	bool searchPassword(const std::string &key);
	bool displayPasswordsParentNames(const std::string &none); //only for function pointer map, string none is not neccessary

	bool directoryOpen;

private:
	bool isFileExist(const std::string &fileName);
	std::string getInput(const std::string &command);
	std::string readFile(const std::string &path);
	std::string createPath(const std::string &fileName);
	std::unique_ptr<Encrypt> encrypter;
	const static std::vector<std::string> commandList;
};


#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <memory>
#include <experimental/filesystem>
#include "picosha2.h"
#include "BlowfishEncrypt.h"

const std::string DIRECTORY = "C:/PassFolder";
const std::string VERIFY_PASSWORD = "verify_password";

class Database
{
public:
	Database();
	~Database();
	bool isVerifiedUser();
	bool addPassword(std::string key);
	bool removePassword(std::string key);
	bool searchPassword(std::string key);
	void displayPasswordsParentNames();

	bool directoryOpen;

private:
	bool isFileExist(std::string fileName);
	std::string getInput(std::string command);
	std::string readFile(std::string path);
	std::string createPath(std::string fileName);
	std::unique_ptr<BlowfishEncrypt> encrypter;
};


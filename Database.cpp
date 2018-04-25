#include "Database.h"

Database::Database()
{
	namespace fs = std::experimental::filesystem::v1;
	directoryOpen = (fs::exists(DIRECTORY) || fs::create_directory(DIRECTORY));
	encrypter = std::make_unique<BlowfishEncrypt>();
}


Database::~Database()
{
}

bool Database::isVerifiedUser()
{
	std::ifstream infile(VERIFY_PASSWORD.c_str());
	if (infile.good()) {
		infile.close();
		std::string input = getInput("Enter user password");
		std::string inputHash;
		picosha2::hash256_hex_string(input, inputHash);
		std::string fileString = readFile(VERIFY_PASSWORD);
		return fileString == inputHash;
	}
	else {
		std::string pass = getInput("Enter a password to be used to verify your identity later.");
		std::string passHash;
		picosha2::hash256_hex_string(pass, passHash);
		std::ofstream outfile(createPath(VERIFY_PASSWORD));
		outfile << passHash << std::endl;
		outfile.close();
		return true;
	}
}

bool Database::addPassword(std::string key)
{
	std::string path = encrypter->encrypt(key);
	if (isFileExist(path)) {
		std::cout << "File name already exists." << std::endl;
		return false;
	}
	std::ofstream outfile(createPath(path));
	if (!outfile.good()) {
		std::cout << "Path does not exist." << std::endl;
		return false;
	}
	std::string input = getInput("");
	std::string inputEncrypt = encrypter->encrypt(input);
	outfile << inputEncrypt << std::endl;
	outfile.close();
	return true;
}

bool Database::removePassword(std::string key)
{
	std::string path = encrypter->encrypt(key);
	if (!isFileExist(path)) {
		std::cout << "File does not exist." << std::endl;
		return false;
	}
	std::remove(createPath(path).c_str());
	return true;
}

bool Database::searchPassword(std::string key)
{
	std::string path = encrypter->encrypt(key);
	if (!isFileExist(path)) {
		std::cout << "File does not exist." << std::endl;
		return false;
	}
	std::string encryptedText = readFile(path);
	std::string text = encrypter->decrypt(encryptedText);
	std::cout << text << std::endl;
	return true;
}

void Database::displayPasswordsParentNames()
{
	namespace fs = std::experimental::filesystem::v1;
	for (auto & filename : fs::directory_iterator(DIRECTORY)) {
		if (filename != VERIFY_PASSWORD + ".txt") {
			std::cout << filename << std::endl;
		}
	}
}

bool Database::isFileExist(std::string fileName)
{
	bool fileExists = false;
	std::ifstream infile(createPath(fileName));
	if (infile.good()) {
		fileExists = true;
		infile.close();
	}
	return fileExists;
}

std::string Database::getInput(std::string command)
{
	if (!command.empty()) {
		std::cout << command << std::endl;
	}
	std::string input;
	std::getline(std::cin, input);
	return input;
}

std::string Database::readFile(std::string path)
{
	std::ifstream infile(createPath(path));
	if (!infile.good()) return NULL;
	std::string fileString;
	std::getline(infile, fileString);
	infile.close();
	return fileString;
}

std::string Database::createPath(std::string fileName)
{
	return DIRECTORY + "/" + fileName + ".txt";
}
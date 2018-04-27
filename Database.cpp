#include "Database.h"

/*const std::map<std::string, Database::DatabaseFunction> Database::functionMap =
{
	{ "add", (Database::DatabaseFunction)&Database::addPassword },
	{ "verify", (Database::DatabaseFunction)&Database::isVerifiedUser },
	{ "delete", (Database::DatabaseFunction)&Database::removePassword },
	{ "search", (Database::DatabaseFunction)&Database::searchPassword },
	{ "showall", (Database::DatabaseFunction)&Database::displayPasswordsParentNames }
};*/

const std::vector<std::string> Database::commandList = {
	"add",
	"verify",
	"delete",
	"search",
	"showall"
};

Database::Database(std::shared_ptr<Messenger> messenger)
{
	this->messenger = messenger;
	namespace fs = std::experimental::filesystem::v1;
	directoryOpen = (fs::exists(DIRECTORY) || fs::create_directory(DIRECTORY));
	encrypter = std::make_unique<Encrypt>();
}


Database::~Database()
{

}

const bool Database::callCommand(std::string command, std::string key)
{
	if (command == commandList[0]) return addPassword(key);
	if (command == commandList[1]) return isVerifiedUser(key);
	if (command == commandList[2]) return removePassword(key);
	if (command == commandList[3]) return searchPassword(key);
	if (command == commandList[4]) return displayPasswordsParentNames(key);
}

bool Database::isVerifiedUser(const std::string &none)
{
	std::ifstream infile(createPath(VERIFY_PASSWORD).c_str());
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

bool Database::addPassword(const std::string &key)
{
	std::string path = key;
	if (isFileExist(path)) {
		messenger->msg("File does not exist.");
		return false;
	}
	std::ofstream outfile(createPath(path));
	if (!outfile.good()) {
		messenger->msg("Path does not exist.");
		return false;
	}
	std::string input = getInput("");
	std::string inputEncrypt = encrypter->encrypt(input);
	outfile << inputEncrypt << std::endl;
	outfile.close();
	return true;
}

bool Database::removePassword(const std::string &key)
{
	std::string path = key;
	if (!isFileExist(path)) {
		messenger->msg("File does not exist.");
		return false;
	}
	std::remove(createPath(path).c_str());
	return true;
}

bool Database::searchPassword(const std::string &key)
{
	std::string path = key;
	if (!isFileExist(path)) {
		messenger->msg("File does not exist.");
		return false;
	}
	std::string encryptedText = readFile(path);
	std::string text = encrypter->decrypt(encryptedText);
	messenger->msg(text);
	messenger->storePassword(text);
	return true;
}

bool Database::displayPasswordsParentNames(const std::string &none) //only for function pointer map
{
	namespace fs = std::experimental::filesystem::v1;
	for (auto & filename : fs::directory_iterator(DIRECTORY)) {
		if (filename != VERIFY_PASSWORD + ".txt") {
			std::cout << filename << std::endl;
		}
	}
	return true;
}

bool Database::isFileExist(const std::string &fileName)
{
	bool fileExists = false;
	std::ifstream infile(createPath(fileName));
	if (infile.good()) {
		fileExists = true;
		infile.close();
	}
	return fileExists;
}

std::string Database::getInput(const std::string &command)
{
	if (!command.empty()) {
		messenger->msg(command);
	}
	std::string input;
	std::getline(std::cin, input);
	return input;
}

std::string Database::readFile(const std::string &path)
{
	std::ifstream infile(createPath(path));
	if (!infile.good()) return NULL;
	std::string fileString;
	std::getline(infile, fileString);
	infile.close();
	return fileString;
}

std::string Database::createPath(const std::string &fileName)
{
	return DIRECTORY + "/" + fileName + ".txt";
}
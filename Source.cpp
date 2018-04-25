#include "Database.h"

int main() {
	//Test Driver Code
	Database db;
	db.isVerifiedUser();
	db.isVerifiedUser();
	db.addPassword("one");
	db.addPassword("one");
	db.addPassword("two");
	db.removePassword("two");
	db.searchPassword("one");
	db.displayPasswordsParentNames();
	std::cin.get();
}
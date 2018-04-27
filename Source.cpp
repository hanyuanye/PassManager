#include "InputHandler.h"

int main() {
	//Test Driver Code
	InputHandler ih;
	while (!ih.callCommand("verify")) {
		std::cout << "Password not Verified." << std::endl;
	}
	std::cout << "Password Verified." << std::endl;
	while (true) {
		std::string input = ih.getInput();
		ih.callCommand(input);
	}
	std::cin.get();
}
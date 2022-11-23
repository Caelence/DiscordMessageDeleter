#include "getInfo.h"

void getToken(Discord& discordDeleter) {
	std::cout << "Enter your Discord token: ";
	std::cin >> discordDeleter.token;
	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
}

void getChannel(Discord& discordDeleter) {
	std::cout << "Enter the channel you want to delete from: ";
	std::cin >> discordDeleter.channelID;
	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
}

bool getTestToken(Discord& discordDeleter) {
	if (discordDeleter.testToken()) {
		std::cout << "[+] - Token is valid" << std::endl;
		std::cout << "[+] - Set userID to: " << discordDeleter.getUserID() << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
	}
	else {
		std::cerr << "[!] - Token is invalid - exiting" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		return false;
	}

	return true;
}

bool getMessagesToDelete(Discord& discordDeleter) {
	int amountToDelete{};
	char deleteAllMessages{};

	std::cout << "Do you want to delete all messages sent by you? (y/N): ";
	std::cin.ignore();
	std::cin.get(deleteAllMessages);
	deleteAllMessages = std::toupper(deleteAllMessages);
	
	if (deleteAllMessages == '\n' || deleteAllMessages == 'N') {
		std::cout << "Enter the amount of messages you wish to delete: ";
		std::cin >> amountToDelete;

		if (amountToDelete > 0)
			discordDeleter.amountToDelete = { amountToDelete };
		else {
			std::cerr << "[!] - Invalid amount entered. Please enter a number higher than 0" << std::endl;
			getMessagesToDelete(discordDeleter);
		}
	}
	else if (deleteAllMessages == 'Y') {
		discordDeleter.amountToDelete = { 0 };
	}
	else {
		std::cerr << "[!] - Please enter a valid option and try again." << std::endl;
		return false;
	}

	return true;
}
#include "getInfo.h"

void printStart() {
	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "  _____  _                       _   __  __                                  _____       _      _            " << std::endl;
	std::cout << " |  __ \\(_)                     | | |  \\/  |                                |  __ \\     | |    | |           " << std::endl;
	std::cout << " | |  | |_ ___  ___ ___  _ __ __| | | \\  / | ___  ___ ___  __ _  __ _  ___  | |  | | ___| | ___| |_ ___ _ __ " << std::endl;
	std::cout << " | |  | | / __|/ __/ _ \\| '__/ _` | | |\\/| |/ _ \\/ __/ __|/ _` |/ _` |/ _ \\ | |  | |/ _ \\ |/ _ \\ __/ _ \\ '__|" << std::endl;
	std::cout << " | |__| | \\__ \\ (_| (_) | | | (_| | | |  | |  __/\\__ \\__ \\ (_| | (_| |  __/ | |__| |  __/ |  __/ ||  __/ |   " << std::endl;
	std::cout << " |_____/|_|___/\\___\\___/|_|  \\__,_| |_|  |_|\\___||___/___/\\__,_|\\__, |\\___| |_____/ \\___|_|\\___|\\__\\___|_|   " << std::endl;
	std::cout << "                                                                 __/ |                                       " << std::endl;
	std::cout << "                                                                |___/                                        " << std::endl;
	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
}

void getToken(Discord& discordDeleter) {
	std::cout << "Enter your Discord token: ";
	std::cin >> discordDeleter.token;
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

void getChannel(Discord& discordDeleter) {
	std::cout << "Enter the channel you want to delete from: ";
	std::cin >> discordDeleter.channelID;
	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
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

bool manualChannelID(Discord& discordDeleter) {
	char manuallyEnterID{};

	std::cout << "Do you want to manually enter the channel ID? (y/N): ";
	std::cin.ignore();
	std::cin.get(manuallyEnterID);
	manuallyEnterID = std::toupper(manuallyEnterID);

	if (manuallyEnterID == '\n' || manuallyEnterID == 'N') {
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		if (!usernamesOrGroups(discordDeleter))
			return false;
	}
	else if (manuallyEnterID == 'Y') {
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		getChannel(discordDeleter);
	}
	else {
		std::cerr << "[!] - Please enter a valid option and try again." << std::endl;
		return false;
	}

	return true;
}

bool usernamesOrGroups(Discord& discordDeleter) {
	char usernameOrGroup{};

	std::cout << "Do you want to choose from usernames or groups? (U/g): ";
	std::cin.get(usernameOrGroup);
	usernameOrGroup = std::toupper(usernameOrGroup);

	if (usernameOrGroup == '\n' || usernameOrGroup == 'U') {
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		if (!getUsernames(discordDeleter)) {
			return false;
		}
	}
	else if (usernameOrGroup == 'G') {
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		if (!getGroups(discordDeleter)) {
			return false;
		}
	}
	else {
		std::cerr << "[!] - Please enter a valid option and try again." << std::endl;
		return false;
	}

	return true;
}

bool validateResponse(Discord& discordDeleter, int& selection, bool usernameOrGroup) {
	if (usernameOrGroup) {
		if (selection <= discordDeleter.usernameAndChannelID.size()) {
			std::map<std::string, std::string>::iterator findMatchIt{ discordDeleter.usernameAndChannelID.begin() };
			int findMatch{ 1 };

			while (findMatch != selection) {
				findMatchIt++;
				findMatch++;
			}

			discordDeleter.channelID = { findMatchIt->second };
			std::cout << "[+] - Selected user: " << findMatchIt->first << ", with ID: " << findMatchIt->second << std::endl;
			std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		}
		else {
			std::cerr << "[!] - Please enter a valid option and try again." << std::endl;
			return false;
		}
	}
	else {
		if (selection <= discordDeleter.groupNameAndChannelID.size()) {
			std::map<std::string, std::string>::iterator findMatchIt{ discordDeleter.groupNameAndChannelID.begin() };
			int findMatch{ 1 };

			while (findMatch != selection) {
				findMatchIt++;
				findMatch++;
			}

			discordDeleter.channelID = { findMatchIt->second };
			std::cout << "[+] - Selected group: " << findMatchIt->first << ", with ID: " << findMatchIt->second << std::endl;
			std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		}
		else {
			std::cerr << "[!] - Please enter a valid option and try again." << std::endl;
			return false;
		}
	}

	return true;
}

bool getUsernames(Discord& discordDeleter) {
	if (discordDeleter.getChannels()) {
		discordDeleter.dmUsernamesTotal++;
		std::map<std::string, std::string>::iterator usernameAndChannelIDIt{ discordDeleter.usernameAndChannelID.begin() };

		for (size_t i{ 0 }; i < discordDeleter.usernameAndChannelID.size(); i++) {
			if (usernameAndChannelIDIt != discordDeleter.usernameAndChannelID.end()) {
				std::cout << "[" << discordDeleter.dmUsernamesTotal << "] Username: " << usernameAndChannelIDIt->first << ", ID: " << usernameAndChannelIDIt->second << std::endl;
				usernameAndChannelIDIt++;
				discordDeleter.dmUsernamesTotal++;
			}
		}

		discordDeleter.dmUsernamesTotal--;
		int userSelection{};

		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Enter the number corresponding to the user you want to delete messages from: ";
		std::cin >> userSelection;
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;

		if (!validateResponse(discordDeleter, userSelection, true)) {
			return false;
		}
	}
	else {
		std::cerr << "[!] - Unable to get channels from Discord API. Please try enter the channel ID manually." << std::endl;
		getChannel(discordDeleter);
	}

	return true;
}

bool getGroups(Discord& discordDeleter) {
	if (discordDeleter.getChannels()) {
		discordDeleter.dmGroupsTotal++;
		std::map<std::string, std::string>::iterator groupNameAndChannelIDIt{ discordDeleter.groupNameAndChannelID.begin() };

		for (size_t i{ 0 }; i < discordDeleter.groupNameAndChannelID.size(); i++) {
			if (groupNameAndChannelIDIt != discordDeleter.groupNameAndChannelID.end()) {
				std::cout << "[" << discordDeleter.dmGroupsTotal << "] Group Name: " << groupNameAndChannelIDIt->first << ", ID: " << groupNameAndChannelIDIt->second << std::endl;
				groupNameAndChannelIDIt++;
				discordDeleter.dmGroupsTotal++;
			}
		}

		discordDeleter.dmGroupsTotal--;
		int groupSelection{};

		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Enter the number corresponding to the group you want to delete messages from: ";
		std::cin >> groupSelection;
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;

		if (!validateResponse(discordDeleter, groupSelection, false)) {
			return false;
		}
	}
	else {
		std::cerr << "[!] - Unable to get channels from Discord API. Please try enter the channel ID manually." << std::endl;
		getChannel(discordDeleter);
	}

	return true;
}
#include "channelID.h"

bool manualChannelID(Discord& discordDeleter) {
	char manuallyEnterID{};

	std::cout << "Do you want to manually enter the channel ID? (y/N Default = N): ";
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

	std::cout << "Do you want to choose from usernames or groups? (U/g Default = U): ";
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
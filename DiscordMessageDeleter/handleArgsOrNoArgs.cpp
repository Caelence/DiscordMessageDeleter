#include "handleArgsOrNoArgs.h"

int argsOrNoArgs(int& argc, char** argv, Discord& discordDeleter) {
	ArgsHandler args(argc, argv);

	if (args.noArgs == true) {
		printStart();

		getToken(discordDeleter);
		if (!getTestToken(discordDeleter)) {
			std::cerr << "[!] - Unable to validate token. Perhaps the internet is out, or the token is incorrect." << std::endl;
			return 1;
		}
		if (!manualChannelID(discordDeleter)) {
			std::cerr << "[!] - Unable to get the channel ID. Perhaps the internet is out, or an invalid channel ID was selected/entered." << std::endl;
			return 1;
		}
		if (!getTestChannel(discordDeleter)) {
			std::cerr << "[!] - Unable to channelID. Perhaps the internet is out, or the channelID is incorrect." << std::endl;
			return 1;
		}
		if (!getMessagesToDelete(discordDeleter)) {
			std::cerr << "[!] - Unable to get the amount of messages to delete. Perhaps you entered an invalid amount." << std::endl;
			return 1;
		}

		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
	}
	else {
		if (!args.handler(discordDeleter)) {
			return 1;
		}

		if (args.setHelp || args.setVersion) {
			return 2;
		}

		if (!args.setToken || !args.setChannel || !args.setAmount) {
			return 0;
		}
	}

	return 3;
}
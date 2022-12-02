#include "ArgsHandler.h"

ArgsHandler::ArgsHandler(int& argc, char** argv)
	: possibleArguments{
		{"-h"},
		{"-v"},
		{"-t"},
		{"-c"},
		{"-a"},
		{"-q"},
	},
	noArgs{ false },
	setHelp{ false },
	setVersion{ false },
	setToken{ false },
	setChannel{ false },
	setAmount{ false }
	{
	if (argc >= 2) {
		for (int i{ 1 }; i < argc; i++) {
			arguments.push_back(argv[i]);
		}
	}
	else {
		noArgs = { true };
	}
}

bool ArgsHandler::handler(Discord& discordDeleter) {
	bool h{ false };
	bool v{ false };
	bool t{ false };
	bool c{ false };
	bool a{ false };
	bool q{ false };

	size_t tokenPositionInArgsVector{};
	size_t channelIDPositionInArgsVector{};
	size_t quantityToDeletePositionInArgsVector{};

	for (size_t i{ 0 }; i < arguments.size(); i++) {
		std::string argument{ arguments.at(i) };

		for (size_t j{ 0 }; j < possibleArguments.size(); j++) {
			if (argument == possibleArguments.at(j)) {
				if (argument == "-h") {
					h = { true };
				}
				else if (argument == "-v") {
					v = { true };
				}
				else if (argument == "-t") {
					tokenPositionInArgsVector = { i };
					t = { true };
				}
				else if (argument == "-c") {
					channelIDPositionInArgsVector = { i };
					c = { true };
				}
				else if (argument == "-a") {
					a = { true };
				}
				else if (argument == "-q") {
					quantityToDeletePositionInArgsVector = { i };
					q = { true };
				}
			}
		}
	}

	if (h) {
		handleH();
		return true;
	}
	else if (v) {
		handleV();
		return true;
	}

	if (t && c && a) {
		if (handleT(tokenPositionInArgsVector, discordDeleter) && handleC(channelIDPositionInArgsVector, discordDeleter)) {
			handleA(discordDeleter);
			return true;
		}
		else {
			return false;
		}
	}
	else if (t && c && q) {
		if (handleT(tokenPositionInArgsVector, discordDeleter) && handleC(channelIDPositionInArgsVector, discordDeleter) && handleQ(quantityToDeletePositionInArgsVector, discordDeleter)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		std::cerr << "[!] - Invalid amount of arguments" << std::endl;
		return false;
	}

}

void ArgsHandler::handleH() {
	setHelp = { true };

	std::cout << "Help." << std::endl;
}

void ArgsHandler::handleV() {
	setVersion = { true };

	std::cout << "DiscordMessageDeleter v2.0" << std::endl;
}

bool ArgsHandler::handleT(size_t& tokenPosInVec, Discord& discordDeleter) {
	size_t sizeOfArguments{ arguments.size() - 1 };

	if (tokenPosInVec + 1 > sizeOfArguments) {
		return false;
	}

	for (const auto& posArgument : possibleArguments) {
		if (arguments.at(tokenPosInVec + 1) == posArgument) {
			std::cerr << "[!] - Token option was specified, but no token was defined after it" << std::endl;
			return false;
		}
	}

	discordDeleter.token = { arguments.at(tokenPosInVec + 1) };

	if (discordDeleter.testToken()) {
		setToken = { true };
		return true;
	}
	else {
		std::cerr << "[!] - Token is invalid - exiting" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		return false;
	}
}

bool ArgsHandler::handleC(size_t& channelPosInVec, Discord& discordDeleter) {
	size_t sizeOfArguments{ arguments.size() - 1 };

	if (channelPosInVec + 1 > sizeOfArguments) {
		std::cerr << "[!] - Channel option was specified, but no channelID was defined after it" << std::endl;
		return false;
	}

	for (const auto& posArgument : possibleArguments) {
		if (arguments.at(channelPosInVec + 1) == posArgument) {
			std::cerr << "[!] - Channel option was specified, but no channelID was defined after it" << std::endl;
			return false;
		}
	}

	discordDeleter.channelID = { arguments.at(channelPosInVec + 1) };

	if (discordDeleter.testChannel()) {
		setChannel = { true };
		return true;
	}
	else {
		std::cerr << "[!] - channelID is invalid - exiting" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
		return false;
	}
}

void ArgsHandler::handleA(Discord& discordDeleter) {
	setAmount = { true };
	discordDeleter.amountToDelete = { 0 };
}

bool ArgsHandler::handleQ(size_t& quantityPosInVec, Discord& discordDeleter) {
	size_t sizeOfArguments{ arguments.size() - 1 };

	if (quantityPosInVec + 1 > sizeOfArguments) {
		std::cerr << "[!] - Quantity option was specified, but no quantity was defined after it " << std::endl;
		return false;
	}

	for (const auto& posArgument : possibleArguments) {
		if (arguments.at(quantityPosInVec + 1) == posArgument) {
			std::cerr << "[!] - Quantity option was specified, but no quantity was defined after it" << std::endl;
			return false;
		}
	}

	int amountToDelete{ std::stoi(arguments.at(quantityPosInVec + 1)) };

	if (amountToDelete > 0) {
		discordDeleter.amountToDelete = { amountToDelete };
		setAmount = { true };
		return true;
	}
	else {
		std::cerr << "[!] - Quantity option was specified, but no quantity was defined after it" << std::endl;
		return false;
	}
}
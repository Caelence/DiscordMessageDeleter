#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Discord.h"

class ArgsHandler {
	std::vector<std::string> arguments;
	std::vector<std::string> possibleArguments;
public:
	bool noArgs;
	bool setHelp;
	bool setVersion;
	bool setToken;
	bool setChannel;
	bool setAmount;

	bool handler(Discord& discordDeleter);
private:
	void handleH();
	void handleV();
	bool handleT(size_t& tokenPosInVec, Discord& discordDeleter);
	bool handleC(size_t& channelPosInVec, Discord& discordDeleter);
	void handleA(Discord& discordDeleter);
	bool handleQ(size_t& quantityPosInVec, Discord& discordDeleter);
public:
	ArgsHandler(int& argc, char** argv);
};


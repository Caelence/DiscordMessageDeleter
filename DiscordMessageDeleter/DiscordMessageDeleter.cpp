﻿#include <string>
#include <iostream>
#include <json/value.h>
#include <vector>
#include <random>
#include "Discord.h"
#include "getInfo.h"
#include <cpr/cpr.h>
#include <Windows.h>

int main() {
	printStart();

	Discord discordDeleter;
	getToken(discordDeleter);
	if (!getTestToken(discordDeleter)) {
		std::cerr << "[!] - Unable to validate token. Perhaps the internet is out, or the token is incorrect." << std::endl;
		return 1;
	}
	if (!manualChannelID(discordDeleter)) {
		std::cerr << "[!] - Unable to get the channel ID. Perhaps the internet is out, or an invalid channel ID was selected/entered." << std::endl;
		return 1;
	}
	if (!getMessagesToDelete(discordDeleter)) {
		std::cerr << "[!] - Unable to get the amount of messages to delete. Perhaps you entered an invalid amount." << std::endl;
	}

	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;

	while (true) {
		std::vector<Json::Value> messageBatch{ discordDeleter.getRecentMessages() };
		Json::Value message;

		if (messageBatch.at(0) == "404") {
			std::cout << "[!] - An incorrect channel ID was set. Please try running the program again with a valid channel ID." << std::endl;
			return 1;
		}
		else if (messageBatch.at(0) == "") {
			std::cout << "[!] - Unable to fetch messages. Might be an issue with the internet." << std::endl;
			return 1;
		}
		else if (messageBatch.at(0) == "Done") {
			break;
		}

		for (size_t i{ 0 }; i < messageBatch.size(); i++) {
			message = { messageBatch.at(i) };

			if (discordDeleter.getUserID() == message["author"]["id"].asString()) {

				if (message.isMember("call")) {
					std::cout << "[+] - Found call at ID: " << message["id"] << ", skipping" << std::endl;
					continue;
				}

				bool status{ discordDeleter.deleteMesssage(message["id"].asString())};

				if (status == true) {
					discordDeleter.deletedMessages++;

					std::cout << "[" << discordDeleter.deletedMessages << "] - Successfully deleted message, ID: " << message["id"].asString() << std::endl;
				}
				else {
					discordDeleter.timesRateLimited++;

					if (discordDeleter.timesRateLimited == 3) {
						discordDeleter.timesRateLimited = { 0 };
						int randNum = rand() % (10 - 30 + 1) + 10;

						std::cout << "[!] - Rate limited 3 times now, taking a break for: " << randNum << " seconds" << std::endl;

						Sleep(randNum * 1000);
					}
					else {
						std::cout << "[!] - Rate limited, waiting " << discordDeleter.rateLimit << " seconds" << std::endl;

						Sleep(discordDeleter.rateLimit * 1000);
					}

					i--;
				}

				if (discordDeleter.amountToDelete == 0) {
					continue;
				}
				else if (discordDeleter.deletedMessages == discordDeleter.amountToDelete) {
					break;
				}
			}
		}

		if (discordDeleter.deletedMessages == discordDeleter.amountToDelete) {
			break;
		}
	}
	
	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "[+] - Done deleting all messages [" << discordDeleter.deletedMessages << "] in channel " << discordDeleter.channelID << std::endl;
	std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;

	system("pause");
}
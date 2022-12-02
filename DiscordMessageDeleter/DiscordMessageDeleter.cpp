#include <string>
#include <iostream>
#include <json/value.h>
#include <cpr/cpr.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include "Discord.h"
#include "printStartEnd.h"
#include "handleArgsOrNoArgs.h"

using namespace std::literals::chrono_literals;

int main(int argc, char** argv) {
	Discord discordDeleter;

	switch (argsOrNoArgs(argc, argv, discordDeleter)) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 0;
			break;
	}

	while (true) {
		std::vector<Json::Value> messageBatch{ discordDeleter.getRecentMessages() };
		Json::Value message;

		if (messageBatch.at(0) == "404") {
			std::cerr << "[!] - An incorrect channel ID was set. Please try running the program again with a valid channel ID." << std::endl;
			return 1;
		}
		else if (messageBatch.at(0) == "") {
			std::cerr << "[!] - Unable to fetch messages. Might be an issue with the internet." << std::endl;
			return 1;
		}
		else if (messageBatch.at(0) == "Done") {
			break;
		}

		for (size_t i{ 0 }; i < messageBatch.size(); i++) {
			message = { messageBatch.at(i) };

			if (discordDeleter.getUserID() == message["author"]["id"].asString()) {

				if (message["type"].asString() == "1") {
					std::cout << "[+] - Found added user at ID: " << message["id"] << ", skipping" << std::endl;
					continue;
				}
				else if (message["type"].asString() == "2") {
					std::cout << "[+] - Found removed user at ID: " << message["id"] << ", skipping" << std::endl;
					continue;
				} 
				else if (message.isMember("call")) {
					std::cout << "[+] - Found call at ID: " << message["id"] << ", skipping" << std::endl;
					continue;
				}
				else if (message["type"].asString() == "4") {
					std::cout << "[+] - Found Channel Name Change at ID: " << message["id"] << ", skipping" << std::endl;
					continue;
				}
				else if (message["type"].asString() == "5") {
					std::cout << "[+] - Found Channel Icon Change at ID: " << message["id"] << ", skipping" << std::endl;
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

						std::this_thread::sleep_for(randNum * 1000ms);
					}
					else {
						std::cout << "[!] - Rate limited, waiting " << discordDeleter.rateLimit << " seconds" << std::endl;

						std::this_thread::sleep_for(discordDeleter.rateLimit * 1000ms);
					}

					i--;
				}

				if (discordDeleter.deletedMessages == discordDeleter.amountToDelete) {
					break;
				}
			}
		}

		if (discordDeleter.deletedMessages == discordDeleter.amountToDelete) {
			break;
		}
	}

	printEnd(discordDeleter);
}
#pragma once
#include <string>
#include <map>
#include <vector>
#include <cpr/cpr.h>
#include "base64.h"
#include "stringToJson.h"

class Discord {
	std::string userID;
	std::string lastMessage;
public:
	std::string token;
	std::string channelID;
	int amountToDelete;
	int deletedMessages;
	int timesRateLimited;
	int dmUsernamesTotal;
	int dmGroupsTotal;
	double rateLimit;
	std::map<std::string, std::string> usernameAndChannelID;
	std::map<std::string, std::string> groupNameAndChannelID;

	Discord()
		: dmUsernamesTotal{ 0 },
		  dmGroupsTotal{ 0 },
		  amountToDelete { -1 },
		  deletedMessages{ 0 },
		  timesRateLimited {0},
		  rateLimit {0.0},
		  userID{""},
		  lastMessage{""},
		  token{""},
		  channelID{""}
	      {}

	bool testToken();
	bool deleteMesssage(std::string messageID);
	bool getChannels();
	std::string getUserID();
	std::vector<Json::Value> getRecentMessages();
};
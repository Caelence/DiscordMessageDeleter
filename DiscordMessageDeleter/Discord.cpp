#include "Discord.h"

std::string Discord::getUserID() {
	return userID;
}

bool Discord::testToken() {
	cpr::Response testToken = cpr::Get(cpr::Url{ "https://discord.com/api/v10/users/@me/connections" },
		cpr::Header{ {"authority", "discord.com"},
					 {"authorization", token},
					 {"accept-language", "en-GB"},
					 {"user-agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/1.0.9007 Chrome/91.0.4472.164 Electron/13.6.6 Safari/537.36"},
					 {"accept", "*/*"} });

	if (testToken.status_code == 200) {
		size_t tokenSeparator{ token.find('.') };
		std::string userIDBase64Encoded{};

		if (tokenSeparator != std::string::npos) {
			userIDBase64Encoded = { token.substr(0, tokenSeparator) };
		}
		else {
			return false;
		}

		userID = { base64_decode(userIDBase64Encoded) };

		return true;
	}
	else if (testToken.status_code == 401) {
		return false;
	}
	else {
		//std::cerr << testToken.status_code << std::endl;
		return false;
	}
}

bool Discord::testChannel() {
	cpr::Response testChannel = cpr::Get(cpr::Url{ "https://discord.com/api/v10/channels/" + channelID },
		cpr::Header{ {"authority", "discord.com"},
					 {"authorization", token},
					 {"accept-language", "en-GB"},
					 {"user-agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/1.0.9007 Chrome/91.0.4472.164 Electron/13.6.6 Safari/537.36"},
					 {"accept", "*/*"} });

	if (testChannel.status_code == 200) {
		return true;
	}
	else {
		//std::cerr << testChannel.status_code << std::endl;
		return false;
	}
}

bool Discord::getChannels() {
	cpr::Response dmChannels = cpr::Get(cpr::Url{ "https://discord.com/api/v10/users/@me/channels" },
		cpr::Header{ {"authority", "discord.com"},
					 {"authorization", token},
					 {"accept-language", "en-GB"},
					 {"user-agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/1.0.9007 Chrome/91.0.4472.164 Electron/13.6.6 Safari/537.36"},
					 {"accept", "*/*"} });

	Json::Value dmChannelsJson{ stringToJson(dmChannels.text) };

	if (dmChannels.status_code != 200) {
		return false;
	}

	for (auto& dmChannelJson: dmChannelsJson) {
		if (dmChannelJson["type"] == 1) {
			std::string dmUsername{ dmChannelJson["recipients"][0]["username"].asString() + "#" + dmChannelJson["recipients"][0]["discriminator"].asString() };
			usernameAndChannelID.emplace(dmUsername, dmChannelJson["id"].asString());
		}
		else if (dmChannelJson["type"] == 3) {
			std::vector<std::string> dmGroupNames;
			std::vector<std::string> dmGroupUsernames{};

			if (dmChannelJson["name"].asString() == "") {
				std::string name{};

				for (auto& recipientsJson: dmChannelJson["recipients"]) {
					dmGroupUsernames.emplace_back(recipientsJson["username"].asString());
				}

				for (size_t i{ 0 }; i < dmGroupUsernames.size(); i++) {
					if (dmGroupUsernames.at(i) == dmGroupUsernames.back()) {
						name += dmGroupUsernames.at(i);
					}
					else {
						name += dmGroupUsernames.at(i) + ", ";
					}
				}
				dmGroupNames.emplace_back(name);
			}
			else {
				dmGroupNames.emplace_back(dmChannelJson["name"].asString());
			}

			for (size_t i{ 0 }; i < dmGroupNames.size(); i++) {
				groupNameAndChannelID.emplace(dmGroupNames.at(i), dmChannelJson["id"].asString());
			}
		}
	}

	return true;
}

std::vector<Json::Value> Discord::getRecentMessages() {
	std::vector<Json::Value> messageList;
	std::string channelIDUrl{ "https://discord.com/api/v10/channels/" + channelID + "/messages" };
	cpr::Response recentMessages;

	if (lastMessage == "") {
		recentMessages = cpr::Get(cpr::Url{ channelIDUrl },
			cpr::Header{ {"authority", "discord.com"},
						 {"authorization", token},
						 {"accept-language", "en-GB"},
						 {"user-agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/1.0.9007 Chrome/91.0.4472.164 Electron/13.6.6 Safari/537.36"},
						 {"accept", "*/*"},
						 {"referer", "https://discord.com/channels/@me"} },
			cpr::Parameters{ {"limit", "100"} });
	}
	else {
		recentMessages = cpr::Get(cpr::Url{ channelIDUrl },
			cpr::Header{ {"authority", "discord.com"},
						 {"authorization", token},
						 {"accept-language", "en-GB"},
						 {"user-agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/1.0.9007 Chrome/91.0.4472.164 Electron/13.6.6 Safari/537.36"},
						 {"accept", "*/*"},
						 {"referer", "https://discord.com/channels/@me"} },
			cpr::Parameters{ {"limit", "100"}, {"before", lastMessage} });
	}

	if (recentMessages.status_code == 404) {
		return std::vector<Json::Value>{"404"};
	}
	else if (recentMessages.status_code != 200) {
		return std::vector<Json::Value>{""};
	}

	Json::Value recentMessagesJson{ stringToJson(recentMessages.text) };

	for (auto& recentMessageJson: recentMessagesJson) {
		Json::Value message{ recentMessageJson };

		messageList.emplace_back(message);
	}

	if (messageList.size() == 0) {
		return std::vector<Json::Value>{"Done"};
	}

	lastMessage = { messageList.back()["id"].asString() };

	return messageList;
}

bool Discord::deleteMesssage(std::string messageID) {
	std::string messageIDUrl{ "https://discord.com/api/v10/channels/" + channelID + "/messages/" + messageID };
	cpr::Response deletedMessage = cpr::Delete(cpr::Url{ messageIDUrl },
		cpr::Header{ {"authority", "discord.com"},
					 {"authorization", token},
					 {"accept-language", "en-GB"},
					 {"user-agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/1.0.9007 Chrome/91.0.4472.164 Electron/13.6.6 Safari/537.36"},
					 {"accept", "*/*"} });

	if (deletedMessage.status_code == 204) {
		return true;
	}
	else if (deletedMessage.status_code == 429) {
		Json::Value rateLimitJson{ stringToJson(deletedMessage.text) };
		rateLimit = { rateLimitJson["retry_after"].asDouble() };

		return false;
	}
	else {
		//std::cerr << deletedMessage.status_code << std::endl;
		return false;
	}
}
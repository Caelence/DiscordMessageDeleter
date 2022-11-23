#pragma once
#include <iostream>
#include "Discord.h"
#include "getInfo.h"

bool manualChannelID(Discord& discordDeleter);
bool usernamesOrGroups(Discord& discordDeleter);
bool validateResponse(Discord& discordDeleter, int& selection, bool usernameOrGroup);
bool getUsernames(Discord& discordDeleter);
bool getGroups(Discord& discordDeleter);
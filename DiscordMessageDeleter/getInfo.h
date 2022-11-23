#pragma once
#include "Discord.h"
#include <iostream>
#include <ctype.h>

void printStart();
void getToken(Discord& discordDeleter);
bool getTestToken(Discord& discordDeleter);
void getChannel(Discord& discordDeleter);
bool getMessagesToDelete(Discord& discordDeleter);
bool getUsernames(Discord& discordDeleter);
bool getGroups(Discord& discordDeleter);
bool manualChannelID(Discord& discordDeleter);
bool usernamesOrGroups(Discord& discordDeleter);
bool validateResponse(Discord& discordDeleter, int& selection, bool usernameOrGroup);
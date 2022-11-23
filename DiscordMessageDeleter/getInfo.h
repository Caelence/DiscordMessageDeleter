#pragma once
#include <iostream>
#include "Discord.h"

void getToken(Discord& discordDeleter);
void getChannel(Discord& discordDeleter);

bool getTestToken(Discord& discordDeleter);
bool getMessagesToDelete(Discord& discordDeleter);
#pragma once
#include <iostream>
#include "Discord.h"
#include "ArgsHandler.h"
#include "printStartEnd.h"
#include "getInfo.h"
#include "channelID.h"

int argsOrNoArgs(int& argc, char** argv, Discord& discordDeleter);
#include "stringToJson.h"

// Returns JSON from a string
// Usually from a reponse from libcpr
Json::Value stringToJson(std::string& access)
{
	Json::Value accessJson;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(access, accessJson);
	if (!parsingSuccessful)
	{
		std::cout << "Error parsing the string (stringToJson)" << std::endl;
	}

	return accessJson;
}
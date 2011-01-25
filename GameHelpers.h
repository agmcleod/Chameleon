#include "stdafx.h"
#ifndef GAMEHELPERS_H
#define GAMEHELPERS_H

#include <string>

class GameHelpers
{
public:
	GameHelpers(){}
	std::string& ToLower(std::string& stringToConvert);
};

#endif
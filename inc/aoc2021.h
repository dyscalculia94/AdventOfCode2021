#ifndef AOC2021_H
#define AOC2021_H

#include <map>
#include <string>
#include <functional>

#include "day01.h"
#include "day02.h"

std::map<int, std::function<std::pair<int, int>(std::string)>> days
{
	{1, day01},
	{2, day02}
};


#endif
#ifndef AOC2021_H
#define AOC2021_H

#include <map>
#include <string>
#include <functional>

#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"

std::map<int, std::function<std::pair<long long, long long>(std::string)>> days
{
	{1, day01},
	{2, day02},
	{3, day03},
	{4, day04},
	{5, day05},
	{6, day06},
	{7, day07},
	{8, day08},
	{9, day09}
};


#endif
#include "day01.h"

#include <vector>
#include <fstream>

using Input = std::vector<std::pair<std::pair<int, int>, int>>;

namespace
{
    std::pair<int, int> get_dir(std::string direction)
    {
        std::pair<int, int> dir;

        if (direction == "forward") {
            dir = {1, 0};
        }
        else if (direction == "down") {
            dir = {0, 1};
        }
        else if (direction == "up") {
            dir = {0, -1};
        }

        return dir;
    }

	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		int temp;
        std::string str_temp;
		while (in >> str_temp) {
            in >> temp;
			res.push_back({get_dir(str_temp), temp});
		}

		return res;
	}

    int task1(Input input)
    {
        int result = 0;

		int horizontal = 0;
		int vertical = 0;
		for (auto i : input) {
			auto dir = i.first;
			int len = i.second;

			horizontal += dir.first * len;
			vertical += dir.second * len;
		}

		result = horizontal * vertical;

        return result;
    }

    int task2(Input input)
    {
        int result = 0;

		int aim = 0;
		int horizontal = 0;
		int vertical = 0;
		for (auto i : input) {
			auto dir = i.first;
			int len = i.second;

			horizontal += dir.first * len;
			vertical += dir.first * len * aim;
			aim += dir.second * len;
		}

		result = horizontal * vertical;

        return result;
    }
}

std::pair<int, int> day02(std::string filedir)
{
    Input input = read_input(filedir + "/day02.txt");

    int first = task1(input);
    int second = task2(input);

    return {first, second};
}
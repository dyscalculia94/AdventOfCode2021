#include "day01.h"

#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>

using Input = std::vector<int>;

namespace
{
	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		int temp;
		while (in >> temp) {
			res.push_back(temp);
		}

		return res;
	}

    int task1(Input input)
    {
        int result = 0;

        for (int i = 1; i < input.size(); i++) {
            if (input[i] > input[i - 1]) {
                result++;
            }
        }

        return result;
    }

    int task2(Input input)
    {
        int result = 0;

        int first = input[0] + input[1] + input[2];
        int second = input[1] + input[2] + input[3];

        for (int i = 3; i < input.size(); i++) {
            if (i > 3) {
                first -= input[i - 4];
                first += input[i - 1];
                second -= input[i - 3];
                second += input[i];
            }

            if (first < second) {
                result++;
            }
        }

        return result;
    }
}

std::pair<int, int> day01(std::string filedir)
{
    Input input = read_input(filedir + "/day01.txt");

    int first = task1(input);
    int second = task2(input);

    return {first, second};
}
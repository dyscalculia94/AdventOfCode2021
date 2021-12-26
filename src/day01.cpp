#include "day01.h"

#include <vector>
#include <fstream>

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

    long long task1(Input input)
    {
        long long result = 0;

        for (int i = 1; i < input.size(); i++) {
            if (input[i] > input[i - 1]) {
                result++;
            }
        }

        return result;
    }

    long long task2(Input input)
    {
        long long result = 0;

        size_t size = input.size();

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

std::pair<long long, long long> day01(std::string filedir)
{
    Input input = read_input(filedir + "/day01.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
#include "day06.h"

#include <vector>
#include <array>
#include <fstream>
#include <numeric>

using Input = std::vector<int>;

namespace
{
	long long get_fish(Input input, int days)
	{
		std::array<long long, 9> fish = {0};
		for (auto i : input) {
			fish[i]++;
		}

		for (int i = 0; i < days; i++) {
			long long temp = fish[0];
			for (int j = 1; j < 9; j++) {
				fish[j - 1] = fish[j];
			}
			fish[6] += temp;
			fish[8] = temp;
		}

		return std::accumulate(fish.begin(), fish.end(), 0ll);
	}

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
        long long result = get_fish(input, 80);

        return result;
    }

    long long task2(Input input)
    {
        long long result = get_fish(input, 256);

        return result;
    }
}

std::pair<long long, long long> day06(std::string filedir)
{
    Input input = read_input(filedir + "/day06.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
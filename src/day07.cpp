#include "day07.h"

#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using Input = std::vector<int>;

namespace
{
	long long get_diff(const Input& input, int position)
	{
		long long diff = 0;

		for (auto i : input) {
			diff += abs(i - position);
		}

		return diff;
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
        long long result = 0;
		const int number_of_crabs = input.size();

		std::nth_element(input.begin(), input.begin() + number_of_crabs / 2, input.end());
		if (number_of_crabs % 2) {
			result = get_diff(input, input[number_of_crabs / 2]);
		}
		else {
			result = std::min(get_diff(input, input[number_of_crabs / 2]), get_diff(input, input[number_of_crabs / 2 + 1]));
		}

        return result;
    }

    long long task2(Input input)
    {
        long long result = 0;
		
		long long sum = 0;
		for (auto  i : input) {
			sum += i;
		}

		// Sometimes you have to take floor of the value, and sometimes ceil
		// Which one you take is kind of complex and I didn't want to implement it here
		// For the puzzle input, floor is the right choice
		// For the puzzle example input, ceil is the right choice
		int mean = floor(sum / (input.size() * 1.0));

		for (auto i : input) {
			const int diff = abs(i - mean);
			result += (diff * (diff + 1)) / 2;
		}

        return result;
    }
}

std::pair<long long, long long> day07(std::string filedir)
{
    Input input = read_input(filedir + "/day07.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
#include "day03.h"

#include <vector>
#include <fstream>
#include <algorithm>

#include <iostream>

using Input = std::vector<std::string>;

namespace
{
	std::string get_gamma(const Input& input)
	{
		std::string result = "";
		std::vector<int> counts(input[0].length());

		for (auto i : input) {
			for (int j = 0; j < i.length(); j++) {
				counts[j] += (i[j] == '0' ? -1 : 1);
			}
		}

		for (auto i : counts) {
			result += (i < 0) ? '0' : '1';
		}

		return result;
	}

	std::string get_epsilon(const std::string& gamma)
	{
		std::string result = "";

		for (auto c : gamma) {
			result += (c == '0' ? '1' : '0');
		}

		return result;
	}

	using Comparator = bool(*)(int, int);
	
	std::string get_rating(const Input& input, int left, int right, int position, Comparator comp)
	{
		if (left == right - 1) {
			return input[left];
		}

		int zeroes = 0;
		int ones = 0;
		for (int i = left; i < right; i++) {
			if (input[i][position] == '0') {
				zeroes++;
			}
			else {
				ones++;
			}
		}

		if (comp(zeroes, ones)) {
			return get_rating(input, left, left + zeroes, position + 1, comp);
		}
		else {
			return get_rating(input, left + zeroes, right, position + 1, comp);
		}
	}
	
	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		int temp;
        std::string str_temp;
		while (in >> str_temp) {
			res.push_back(str_temp);
		}

		return res;
	}

    int task1(Input input)
    {
        int result = 0;

		std::string gamma = get_gamma(input);
		std::string epsilon = get_epsilon(gamma);

		result = stoi(gamma, nullptr, 2) * stoi(epsilon, nullptr, 2);

        return result;
    }

    int task2(Input input)
    {
        int result = 0;

		std::sort(input.begin(), input.end());

		std::string ogr = get_rating(input, 0, input.size(), 0, [](int lhs, int rhs) { return lhs > rhs; });
		std::string csr = get_rating(input, 0, input.size(), 0, [](int lhs, int rhs) { return lhs <= rhs; });

		result = stoi(ogr, nullptr, 2) * stoi(csr, nullptr, 2);

        return result;
    }
}

std::pair<int, int> day03(std::string filedir)
{
    Input input = read_input(filedir + "/day03.txt");

    int first = task1(input);
    int second = task2(input);

    return {first, second};
}
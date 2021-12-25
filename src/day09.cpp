#include "day09.h"

#include <vector>
#include <fstream>
#include <queue>

#include <iostream>

using Input = std::vector<std::string>;

namespace
{
	bool is_low_point(const Input& input, int i, int j)
	{
		bool top = true, bottom = true, left = true, right = true;

		if (i > 0) {
			top = input[i - 1][j] > input[i][j];
		}
		if (i < input.size() - 1) {
			bottom = input[i + 1][j] > input[i][j];
		}
		if (j > 0) {
			left = input[i][j - 1] > input[i][j];
		}
		if (j < input[i].size() - 1) {
			right = input[i][j + 1] > input[i][j];
		}

		return top && bottom && left && right;
	}

	long long basin_size(Input& input, int i, int j)
	{
		if (input[i][j] == '9') {
			return 0;
		}

		input[i][j] = '9';

		long long top = 0, bottom = 0, left = 0, right = 0;
		if (i > 0) {
			top = basin_size(input, i - 1, j);
		}
		if (i < input.size() - 1) {
			bottom = basin_size(input, i + 1, j);
		}
		if (j > 0) {
			left = basin_size(input, i, j - 1);
		}
		if (j < input[i].size() - 1) {
			right = basin_size(input, i, j + 1);
		}

		return top + bottom + left + right + 1ll;
	}

	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		std::string str_temp;
		while (!in.eof()) {
			in >> str_temp;
			res.push_back(str_temp);
		}
		
		return res;
	}

    long long task1(Input input)
    {
        long long result = 0;
		
		for (int i = 0; i < input.size(); i++) {
			for (int j = 0; j < input[i].size(); j++) {
				if (is_low_point(input, i, j)) {
					result += input[i][j] - '0' + 1;
				}
			}
		}

        return result;
    }

    long long task2(Input input)
    {
        long long result = 1;
		std::priority_queue<long long> basins;

		for (int i = 0; i < input.size(); i++) {
			for (int j = 0; j < input[i].size(); j++) {
				if (input[i][j] != '9') {
					long long temp = basin_size(input, i, j);
					basins.push(temp);
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			result *= basins.top();
			basins.pop();
		}

        return result;
    }
}

std::pair<long long, long long> day09(std::string filedir)
{
    Input input = read_input(filedir + "/day09.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
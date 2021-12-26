#include "day11.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <stack>
#include <unordered_map>

#include <iostream>

using Input = std::vector<std::vector<int>>;

namespace
{
	void flash(Input& input, std::vector<std::vector<bool>>& flashed, int i, int j)
	{
		flashed[i][j] = true;

		for (int row = -1; row < 2; row++) {
			for (int col = -1; col < 2; col++) {
				int new_row = i + row;
				int new_col = j + col;

				if (new_row >= 0 && new_row < input.size() && new_col >= 0 && new_col < input[new_row].size()) {
					input[new_row][new_col]++;
					
					if (input[new_row][new_col] > 9 && !flashed[new_row][new_col]) {
						flash(input, flashed, new_row, new_col);
					}
				}
			}
		}
	}

	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		std::string str_temp;
		while (!in.eof()) {
			in >> str_temp;
			
			std::vector<int> temp;
			for (int i = 0; i < str_temp.length(); i++) {
				temp.push_back(str_temp[i] - '0');
			}
			res.push_back(temp);
		}
		
		return res;
	}

    long long task1(Input input)
    {
        long long result = 0;
		
		constexpr int size = 10;
		for (int step = 0; step < 100; step++) {
			std::vector<std::vector<bool>> flashed(size, std::vector<bool>(size, false));

			// Increase the enery level of each octopus by 1
			for (int i = 0; i < input.size(); i++) {
				for (int j = 0; j < input[i].size(); j++) {
					input[i][j]++;
				}
			}

			// Each octopus with an energy level of 10 or more flashes
			for (int i = 0; i < input.size(); i++) {
				for (int j = 0; j < input[i].size(); j++) {
					if (input[i][j] > 9 && !flashed[i][j]) {
						flash(input, flashed, i, j);
					}
				}
			}

			// Reset energy level of each octopus that flashed to 0
			for (int i = 0; i < input.size(); i++) {
				for (int j = 0; j < input[i].size(); j++) {
					if (input[i][j] > 9) {
						input[i][j] = 0;
					}
				}
			}

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (flashed[i][j]) {
						result++;
					}
				}
			}
		}

        return result;
    }

    long long task2(Input input)
    {
        long long result = 0;
		
		constexpr int size = 10;
		int count = 0;
		while (count < 100) {
			std::vector<std::vector<bool>> flashed(size, std::vector<bool>(size, false));

			count = 0;
			result++;

			// Increase the enery level of each octopus by 1
			for (int i = 0; i < input.size(); i++) {
				for (int j = 0; j < input[i].size(); j++) {
					input[i][j]++;
				}
			}

			// Each octopus with an energy level of 10 or more flashes
			for (int i = 0; i < input.size(); i++) {
				for (int j = 0; j < input[i].size(); j++) {
					if (input[i][j] > 9 && !flashed[i][j]) {
						flash(input, flashed, i, j);
					}
				}
			}

			// Reset energy level of each octopus that flashed to 0
			for (int i = 0; i < input.size(); i++) {
				for (int j = 0; j < input[i].size(); j++) {
					if (input[i][j] > 9) {
						input[i][j] = 0;
					}
				}
			}

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (flashed[i][j]) {
						count++;
					}
				}
			}
		}

        return result;
    }
}

std::pair<long long, long long> day11(std::string filedir)
{
    Input input = read_input(filedir + "/day11.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
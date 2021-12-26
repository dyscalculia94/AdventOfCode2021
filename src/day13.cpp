#include "day13.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

#include <iostream>

using Input = std::pair<std::vector<std::pair<int, int>>,
						std::vector<std::pair<char, int>>>;

namespace
{
	void fold_paper(std::set<std::pair<int, int>>& map, std::pair<char, int> fold, int& width, int& height)
	{
		if (fold.first == 'x') {
			width = fold.second;
		}
		else {
			height = fold.second;
		}

		std::vector<std::pair<int, int>> additional_dots;
		for (auto dot : map) {
			if (fold.first == 'x') {
				if (dot.first > width) {
					int diff = dot.first - width;
					additional_dots.push_back({width - diff, dot.second});
				}
			}
			else {
				if (dot.second > height) {
					int diff = dot.second - height;
					additional_dots.push_back({dot.first, height - diff});
				}
			}
		}

		for (auto dot : additional_dots) {
			map.insert(dot);
		}
	}

	long long count(const std::set<std::pair<int, int>>& map, int width, int height)
	{
		long long count = 0;

		for (auto dot : map) {
			if (dot.first < width && dot.second < height) {
				count++;
			}
		}

		return count;
	}

	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		std::vector<std::pair<int, int>> dots;
		for (int i = 0; i < 794; i++) {
			int x, y;
			in >> x >> y;
			dots.push_back({x, y});
		}

		std::vector<std::pair<char, int>> folds;
		while (!in.eof()) {
			std::string temp, dir;
			int pos;
			in >> temp >> temp >> dir >> pos;
			folds.push_back({dir[0], pos});
		}
		
		return {dots, folds};
	}

    long long task1(Input input)
    {
        long long result = 0;

		int width = 0;
		int height = 0;
		std::set<std::pair<int, int>> map;
		for (auto dot : input.first) {
			width = std::max(width, dot.first);
			height = std::max(height, dot.second);
			map.insert(dot);
		}
		width++;
		height++;

		fold_paper(map, input.second[0], width, height);

		result = count(map, width, height);

        return result;
    }

    long long task2(Input input)
    {
        long long result = 0;

		int width = 0;
		int height = 0;
		std::set<std::pair<int, int>> map;
		for (auto dot : input.first) {
			width = std::max(width, dot.first);
			height = std::max(height, dot.second);
			map.insert(dot);
		}
		width++;
		height++;

		for (auto fold : input.second) {
			fold_paper(map, fold, width, height);
		}

		std::vector<std::vector<char>> matrix(height, std::vector<char>(width, ' '));

		for (auto dot : map) {
			if (dot.first >= 0 && dot.first < width && dot.second >= 0 && dot.second < height) {
				matrix[dot.second][dot.first] = '#';
			}
		}

		for (auto i : matrix) {
			for (auto j : i) {
				std::cout << j;
			}
			std::cout << std::endl;
		}

        return result;
    }
}

std::pair<long long, long long> day13(std::string filedir)
{
    Input input = read_input(filedir + "/day13.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
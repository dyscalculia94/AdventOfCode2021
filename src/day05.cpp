#include "day05.h"

#include <vector>
#include <array>
#include <fstream>

#include <iostream>

using Input = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>;

namespace
{
	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		int x1, x2, y1, y2;
		while (!in.eof()) {
			in >> x1 >> y1 >> x2 >> y2;
			res.push_back({{x1, y1}, {x2, y2}});
		}
		
		return res;
	}

    long long task1(Input input)
    {
        long long result = 0;
		std::array<std::array<int, 1000>, 1000> map = {{0}};
		
		for (auto i : input) {
			auto a = i.first;
			auto b = i.second;

			const int xdiff = a.first - b.first;
			const int ydiff = a.second - b.second;
			if (!xdiff || !ydiff) {
				const int xstep = xdiff ? -xdiff / abs(xdiff) : 0;
				const int ystep = ydiff ? -ydiff / abs(ydiff) : 0;

				int x = a.first;
				int y = a.second;
				const int steps = std::max(abs(xdiff), abs(ydiff));
				for (int j = 0; j <= steps; j++) {
					int temp = ++map[x + j * xstep][y + j * ystep];
					if (temp == 2) {
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
		std::array<std::array<int, 1000>, 1000> map = {{0}};

		for (auto i : input) {
			auto a = i.first;
			auto b = i.second;

			const int xdiff = a.first - b.first;
			const int ydiff = a.second - b.second;
			const int xstep = xdiff ? -xdiff / abs(xdiff) : 0;
			const int ystep = ydiff ? -ydiff / abs(ydiff) : 0;

			int x = a.first;
			int y = a.second;
			const int steps = std::max(abs(xdiff), abs(ydiff));
			for (int j = 0; j <= steps; j++) {
				int temp = ++map[x + j * xstep][y + j * ystep];
				if (temp == 2) {
					result++;
				}
			}
		}

        return result;
    }
}

std::pair<long long, long long> day05(std::string filedir)
{
    Input input = read_input(filedir + "/day05.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
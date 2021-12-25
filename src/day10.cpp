#include "day10.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <stack>
#include <unordered_map>

#include <iostream>

using Input = std::vector<std::string>;

namespace
{
	std::unordered_map<char, char> matching{{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
	
	bool is_opening(char bracket)
	{
		return bracket == '(' || bracket == '[' || bracket == '{' || bracket == '<';
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
		std::unordered_map<char, long long> value{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
		
		for (auto line : input) {
			std::stack<char> brackets;
			for (auto bracket : line) {
				if (is_opening(bracket)) {
					brackets.push(bracket);
				}
				else {
					char opening = brackets.top();

					if (bracket != matching[opening]) {
						result += value[bracket];
						break;
					}
					else {
						brackets.pop();
					}
				}
			}
		}

        return result;
    }

    long long task2(Input input)
    {
        long long result = 0;
		std::unordered_map<char, long long> value{{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
		std::vector<long long> scores;

		for (auto line : input) {
			std::stack<char> brackets;
			bool corrupted = false;
			for (auto bracket : line) {
				if (is_opening(bracket)) {
					brackets.push(bracket);
				}
				else {
					char opening = brackets.top();

					if (bracket != matching[opening]) {
						corrupted = true;
						break;
					}
					else {
						brackets.pop();
					}
				}
			}

			if (!corrupted && !brackets.empty()) {
				long long score = 0;
				while (!brackets.empty()) {
					score *= 5;
					score += value[matching[brackets.top()]];
					brackets.pop();
				}
				scores.push_back(score);
			}
		}

		std::sort(scores.begin(), scores.end());
		result = scores[scores.size() / 2];

        return result;
    }
}

std::pair<long long, long long> day10(std::string filedir)
{
    Input input = read_input(filedir + "/day10.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
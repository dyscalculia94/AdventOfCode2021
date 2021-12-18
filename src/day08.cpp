#include "day08.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#include <iostream>

using Input = std::vector<std::vector<std::string>>;

namespace
{
	std::string get_difference(std::string left, std::string right)
	{
		std::string diff = "";
		std::sort(left.begin(), left.end());
		std::sort(right.begin(), right.end());
		std::set_difference(right.begin(), right.end(), left.begin(), left.end(), std::back_inserter(diff));

		return diff;
	}

	bool digit_contains_another(std::string left, std::string right)
	{
		return get_difference(left, right).empty();
	}

	using StrVecIt = std::vector<std::string>::const_iterator;
	std::string get_digit_containing_another(StrVecIt begin, StrVecIt end, const std::string& digit)
	{
		for (StrVecIt it = begin; it != end; it++) {
			if (digit_contains_another(*it, digit)) {
				return *it;
			}
		}
	}

	std::string get_zero(const std::vector<std::string>& unknown_digits, const std::string one)
	{
		return get_digit_containing_another(unknown_digits.begin() + 3, unknown_digits.end(), one);
	}

	std::string get_three(const std::vector<std::string>& unknown_digits, const std::string one)
	{
		return get_digit_containing_another(unknown_digits.begin(), unknown_digits.end(), one);
	}

	std::string get_nine(const std::vector<std::string>& unknown_digits, const std::string& four)
	{
		return get_digit_containing_another(unknown_digits.begin() + 3, unknown_digits.end(), four);
	}


	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		std::string str_temp;
		while (!in.eof()) {
			std::vector<std::string> line;
			
			in >> str_temp;
			do {
				line.push_back(str_temp);
				in >> str_temp;
			}
			while (str_temp != "|");

			for (int i = 0; i < 4; i++) {
				in >> str_temp;
				line.push_back(str_temp);
			}

			res.push_back(line);
		}
		
		return res;
	}

    long long task1(Input input)
    {
        long long result = 0;
		
		for (auto line : input) {
			for (int i = 10; i < line.size(); i++) {
				const int len = line[i].length();
				if (len == 2 || len == 3 || len == 4 || len == 7) {
					result++;
				}
			}
		}

        return result;
    }

	// This part is solved logically
	// We already know there are 4 unique digits: 1 (2 segments), 7 (3), 4(4), 8(7)
	// Now we need to check for patterns.
	// Digits 4 and 9 differ in only 2 segments: a and g
	// Digits 5 and 6 differ in only 1 segment: e
	// Digits 5 and 0 differ in 3 segments: c, d, and e
	// So, if we find either of those, we should be able to find others
	// Digits 2, 3, and 5 are all of the same length and have 3 segments in common: a, d, and g 
    long long task2(Input input)
    {
        long long result = 0;
		
		for (auto line : input) {
			std::vector<std::string> unknown_digits(line.begin(), line.begin() + 10);
			std::sort(unknown_digits.begin(), unknown_digits.end(), [](std::string a, std::string b) { return a.length() < b.length(); });

			std::vector<std::string> digits(10);
			// Unknown digits: 1 7 4 2 3 5 0 6 9 8
			// Unique digits
			digits[1] = unknown_digits[0]; 
			digits[4] = unknown_digits[2];
			digits[7] = unknown_digits[1];
			digits[8] = unknown_digits[9];
			unknown_digits.erase(unknown_digits.begin(), unknown_digits.begin() + 3);
			unknown_digits.erase(unknown_digits.end());

			// Unknown digits: 2 3 5 0 6 9
			digits[9] = get_nine(unknown_digits, digits[4]);
			unknown_digits.erase(std::find(unknown_digits.begin(), unknown_digits.end(), digits[9]));

			// Unknown digits: 2 3 5 0 6
			digits[0] = get_zero(unknown_digits, digits[1]);
			unknown_digits.erase(std::find(unknown_digits.begin(), unknown_digits.end(), digits[0]));

			// Unknown digits: 2 3 5 6
			digits[6] = unknown_digits.back();
			unknown_digits.erase(unknown_digits.end());

			// Unknown digits: 2 3 5
			digits[3] = get_three(unknown_digits, digits[1]);
			unknown_digits.erase(std::find(unknown_digits.begin(), unknown_digits.end(), digits[3]));

			// Unknown digits: 2 5
			digits[5] = digit_contains_another(digits[6], unknown_digits[0]) ? unknown_digits[0] : unknown_digits[1];
			unknown_digits.erase(std::find(unknown_digits.begin(), unknown_digits.end(), digits[5]));

			// Unknown digits: 2
			digits[2] = unknown_digits.front();

			// Mapping current segments to real segments
			std::unordered_map<char, char> mapping;

			mapping['a'] = get_difference(digits[1], digits[7])[0];
			mapping['c'] = get_difference(digits[6], digits[9])[0];
			mapping['d'] = get_difference(digits[0], digits[8])[0];
			mapping['e'] = get_difference(digits[5], digits[6])[0];
			mapping['f'] = get_difference(digits[2], digits[1])[0];
			
			std::string four_and_nine = get_difference(digits[4], digits[9]);
			mapping['g'] = four_and_nine[0] != mapping['a'] ? four_and_nine[0] : four_and_nine[1];

			std::string two_and_five = get_difference(digits[2], digits[5]);
			mapping['b'] = two_and_five[0] != mapping['f'] ? two_and_five[0] : two_and_five[1];

			std::vector<std::string> digit_segments = {
				"abcefg",
				"cf",
				"acdeg",
				"acdfg",
				"bcdf",
				"abdfg",
				"abdefg",
				"acf",
				"abcdefg",
				"abcdfg"
			};

			// Convert digit segments to wrong segments
			for (auto& d : digit_segments) {
				for (char& c : d) {
					c = mapping[c];
				}
				std::sort(d.begin(), d.end());
			}

			int number = 0;
			for (int i = 10; i < line.size(); i++) {
				std::sort(line[i].begin(), line[i].end());
				for (int j = 0; j < digit_segments.size(); j++) {
					if (digit_segments[j] == line[i]) {
						number = number * 10 + j;
					}
				}
			}

			result += number;
		}

        return result;
    }
}

std::pair<long long, long long> day08(std::string filedir)
{
    Input input = read_input(filedir + "/day08.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
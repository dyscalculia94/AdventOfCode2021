#include "day14.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#include <iostream>

using Input = std::pair<std::string,
						std::unordered_map<std::string, char>>;

namespace
{

	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		std::string polymer;
		in >> polymer;

		std::unordered_map<std::string, char> map;
		while (!in.eof()) {
			std::string pair, temp;
			in >> pair >> temp;
			map[pair] = temp[0];
		}
		
		return {polymer, map};
	}

    long long task1(Input input)
    {
        long long result = 0;
		std::unordered_map<std::string, long long> counts;
		auto map = input.second;

		std::string polymer = input.first;
		for (int i = 0; i < polymer.length() - 1; i++) {
			std::string pair = std::string() + polymer[i] + polymer[i + 1];
			counts[pair]++;
		}

		for (int i = 0; i < 10; i++) {
			std::unordered_map<std::string, long long> next_counts;

			for (auto pair : counts) {
				char c = map[pair.first];
				std::string next_pair1 = std::string() + pair.first[0] + c;
				std::string next_pair2 = std::string() + c + pair.first[1];

				next_counts[next_pair1] += pair.second;
				next_counts[next_pair2] += pair.second;
			}

			counts = next_counts;
		}

		std::array<long long, 26> letters = {0};
		for (auto pair : counts) {

			letters[pair.first[0] - 'A'] += pair.second;
			letters[pair.first[1] - 'A'] += pair.second;
		}

		letters[polymer.front() - 'A']++;
		letters[polymer.back() - 'A']++;
		
		long long min = letters[polymer.front() - 'A'];
		long long max = 0;
		for (auto& i : letters) {
			i /= 2;
			if (i && i < min) {
				min = i;
			}
			max = std::max(max, i);
		}

		result = max - min;

        return result;
    }

    long long task2(Input input)
    {
        long long result = 0;
		std::unordered_map<std::string, long long> counts;
		auto map = input.second;

		std::string polymer = input.first;
		for (int i = 0; i < polymer.length() - 1; i++) {
			std::string pair = std::string() + polymer[i] + polymer[i + 1];
			counts[pair]++;
		}

		for (int i = 0; i < 40; i++) {
			std::unordered_map<std::string, long long> next_counts;

			for (auto pair : counts) {
				char c = map[pair.first];
				std::string next_pair1 = std::string() + pair.first[0] + c;
				std::string next_pair2 = std::string() + c + pair.first[1];

				next_counts[next_pair1] += pair.second;
				next_counts[next_pair2] += pair.second;
			}

			counts = next_counts;
		}

		std::array<long long, 26> letters = {0};
		for (auto pair : counts) {

			letters[pair.first[0] - 'A'] += pair.second;
			letters[pair.first[1] - 'A'] += pair.second;
		}

		letters[polymer.front() - 'A']++;
		letters[polymer.back() - 'A']++;
		
		long long min = letters[polymer.front() - 'A'];
		long long max = 0;
		for (auto& i : letters) {
			i /= 2;
			if (i && i < min) {
				min = i;
			}
			max = std::max(max, i);
		}

		result = max - min;

        return result;
    }
}

std::pair<long long, long long> day14(std::string filedir)
{
    Input input = read_input(filedir + "/day14.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
#include "day04.h"

#include <vector>
#include <array>
#include <fstream>

using Input = std::pair<std::vector<int>,
						std::vector<std::array<std::array<int, 5>, 5>>>;

namespace
{
	bool is_winning_board(const std::array<std::array<int, 5>, 5> &board)
	{
		for (int i = 0; i < 5; i++) {
			int count = 0;
			for (int j = 0; j < 5; j++) {
				if (board[i][j] == -1) {
					count++;
				}
			}

			if (count == 5) {
				return true;
			}
		}

		for (int i = 0; i < 5; i++) {
			int count = 0;
			for (int j = 0; j < 5; j++) {
				if (board[j][i] == -1) {
					count++;
				}
			}

			if (count == 5) {
				return true;
			}
		}

		return false;
	}

	bool mark(std::array<std::array<int, 5>, 5> &board, int number)
	{
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (board[i][j] == number) {
					board[i][j] = -1;
				}
			}
		}

		return is_winning_board(board);
	}

	int sum_board(const std::array<std::array<int, 5>, 5> &board)
	{
		int sum = 0;

		for (auto row : board) {
			for (auto i : row) {
				if (i != -1) {
					sum += i;
				}
			}
		}

		return sum;
	}
	
	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		std::vector<int> drawn_numbers;
		int temp = 0;
		while (in >> temp) {
			if (temp == -1) {
				break;
			}
			drawn_numbers.push_back(temp);
		}

		std::vector<std::array<std::array<int, 5>, 5>> boards;
		while (!in.eof()) {
			std::array<std::array<int, 5>, 5> board;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					in >> board[i][j];
				}
			}

			boards.push_back(board);
		}

		res = {drawn_numbers, boards};
		return res;
	}

    int task1(Input input)
    {
        int result = -1;

        std::vector<int> drawn_numbers = input.first;
		std::vector<std::array<std::array<int, 5>, 5>> boards = input.second;

		for (auto number : drawn_numbers) {
			for (auto& board : boards) {
				if (mark(board, number)) {
					return sum_board(board) * number;
				}
			}
		}

        return result;
    }

    int task2(Input input)
    {
        int result = -1;

        std::vector<int> drawn_numbers = input.first;
		std::vector<std::array<std::array<int, 5>, 5>> boards = input.second;

		for (auto number : drawn_numbers) {
			for (auto& board : boards) {
				mark(board, number);
			}

			for (int i = 0; i < boards.size(); ) {
				if (is_winning_board(boards[i])) {
					if (boards.size() == 1) {
						return sum_board(boards[0]) * number;
					}
					boards.erase(boards.begin() + i);
				}
				else {
					i++;
				}
			}
		}

        return result;
    }
}

std::pair<int, int> day04(std::string filedir)
{
    Input input = read_input(filedir + "/day04.txt");

    int first = task1(input);
    int second = task2(input);

    return {first, second};
}
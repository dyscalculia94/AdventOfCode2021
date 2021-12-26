#include "day12.h"
#include "graph.h"

#include <vector>
#include <fstream>
#include <algorithm>

#include <iostream>

using Input = std::vector<std::pair<std::string, std::string>>;

namespace
{
	bool is_big_cave(unsigned char cave)
	{
		return std::isupper(cave);
	}

	bool is_special(std::string name)
	{
		return name == "start" || name == "end";
	}

	void dfs1(std::vector<std::string>& paths, std::unordered_map<std::string, bool> visited, aoc::node* node, std::string current_path)
	{
		std::string name = node->get_name();
		current_path += "," + name;

		if (name == "end") {
			paths.push_back(current_path);
			return;
		}

		visited[name] = true;

		int visit = 0;
		for (auto n : node->get_connections()) {
			if (is_big_cave(n->get_name()[0]) || !visited[n->get_name()]) {
				visit++;
				dfs1(paths, visited, n, current_path);
			}
		}

		if (!visit) {
			paths.push_back(current_path);
		}
	}

	void dfs2(std::vector<std::string>& paths, std::unordered_map<std::string, bool> visited, aoc::node* node, std::string current_path, bool twice)
	{
		std::string name = node->get_name();
		current_path += "," + name;

		if (name == "end") {
			paths.push_back(current_path);
			return;
		}

		visited[name] = true;

		int visit = 0;
		for (auto n : node->get_connections()) {
			std::string n_name = n->get_name();
			if (n_name == "c") {
				int a = 5;
			}
			bool big_cave = is_big_cave(n->get_name()[0]);
			bool special = is_special(n->get_name());
			bool small_visited = !big_cave && visited[n->get_name()];
			if (big_cave || !visited[n->get_name()] || (!special && !twice)) {
				visit++;
				dfs2(paths, visited, n, current_path, small_visited ? small_visited : twice);
			}
		}

		if (!visit) {
			paths.push_back(current_path);
		}
	}
	
	void generate_paths(Input input, std::vector<std::string>& paths, int part)
	{
		aoc::graph graph;
		graph.initialise(input);
		
		auto names = graph.get_node_names();
		std::unordered_map<std::string, bool> visited;
		for (auto name : names) {
			visited[name] = false;
		}

		if (part == 1) {
			dfs1(paths, visited, graph.get_start(), "");
		}
		else {
			dfs2(paths, visited, graph.get_start(), "", false);
		}
	}

	Input read_input(std::string filename)
	{
		Input res;
		std::ifstream in(filename);

		std::string lhs, rhs;
		while (!in.eof()) {
			in >> lhs >> rhs;
			res.push_back({lhs, rhs});
		}
		
		return res;
	}

    long long task1(Input input)
    {
        long long result = 0;

		std::vector<std::string> paths;
		generate_paths(input, paths, 1);
		auto new_end = std::remove_if(paths.begin(), paths.end(), [](const std::string& path) { return path.substr(path.length() - 3, 3) != "end"; });
		paths.erase(new_end, paths.end());
		
		result = paths.size();

        return result;
    }

    long long task2(Input input)
    {
        long long result = 0;

		std::vector<std::string> paths;
		generate_paths(input, paths, 2);
		auto new_end = std::remove_if(paths.begin(), paths.end(), [](const std::string& path) { return path.substr(path.length() - 3, 3) != "end"; });
		paths.erase(new_end, paths.end());
		
		result = paths.size();

        return result;
    }
}

std::pair<long long, long long> day12(std::string filedir)
{
    Input input = read_input(filedir + "/day12.txt");

    long long first = task1(input);
    long long second = task2(input);

    return {first, second};
}
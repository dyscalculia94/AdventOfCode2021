#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

namespace aoc
{
	class node
	{
	public:
		node(std::string name) : _name(name) { }

		std::string get_name() { return _name; }

		void add_connection(node* node);
		std::vector<node*> get_connections() { return _connections; }

	private:
		std::string _name;
		std::vector<node*> _connections;
	};

	class graph
	{
	public:
		graph() = default;
		void initialise(const std::vector<std::pair<std::string, std::string>>& pairs);

		node* get_start() { return get_node("start"); }
		node* get_end() { return get_node("end"); }

		std::vector<std::string> get_node_names();
		

	private:
		node* get_node(std::string name);
		node* new_node(std::string name);
		void add_connection(node* lhs, node* rhs);

		std::unordered_map<std::string, node*> _nodes;
	};
}

#endif
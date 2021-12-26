#include "graph.h"

using namespace aoc;

void node::add_connection(node* node)
{
	_connections.push_back(node);
}

void graph::initialise(const std::vector<std::pair<std::string, std::string>>& pairs)
{
	for (auto pair : pairs) {
		node* lhs = get_node(pair.first);
		node* rhs = get_node(pair.second);

		if (!lhs) {
			lhs = new_node(pair.first);
		}
		if (!rhs) {
			rhs = new_node(pair.second);
		}

		add_connection(lhs, rhs);
	}
}

std::vector<std::string> graph::get_node_names()
{
	std::vector<std::string> names;

	for (auto node : _nodes) {
		names.push_back(node.first);
	}

	return names;
}

node* graph::get_node(std::string name)
{
	auto it = _nodes.find(name);

	return it != _nodes.end() ? it->second : nullptr;
}

node* graph::new_node(std::string name)
{
	node* n = new node(name);
	_nodes[name] = n;

	return n;
}

void graph::add_connection(node* lhs, node* rhs)
{
	lhs->add_connection(rhs);
	rhs->add_connection(lhs);
}
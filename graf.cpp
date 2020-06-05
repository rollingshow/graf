#include "stdafx.h"
#include "graf.h"


void Graph::removeNode(Node* node) {
	nodes.erase(node);
	// Remove also from all neighbours list
	for (std::set<Node*>::iterator it = nodes.begin();
		it != nodes.end(); it++) {
		(*it)->removeNeighbour(node);
	}
}
void Graph::addEdge(Node* begin, Node* end) {
	if (nodes.find(begin) == nodes.end())
		return;
	if (nodes.find(end) == nodes.end())
		return;
	begin->addNeighbour(end);
	end->addNeighbour(begin);
}

bool BFS::connected(Node* begin, Node* end) {
	std::queue<Node*> nodes; nodes.push(begin);
	std::set<Node*> visited;
	while (!nodes.empty()) {
		Node* next = nodes.front(); nodes.pop();
		if (end == next) return true;
		visited.insert(next);
		for (node_iterator it = next->nb_begin();
			it != next->nb_end(); it++)
			if (visited.find(*it) == visited.end())
				nodes.push(*it);
	}
	return false;
}

static Way unroll(std::map<Node*, MarkedNode> visited,
	Node* begin, Node* curr) {
	Way way;
	way.length = visited[curr].mark;
	while (curr != begin) {
		way.nodes.push_back(curr);
		curr = visited[curr].prev;
	}
	way.nodes.push_back(begin);
	return way;
}


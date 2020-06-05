#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <set>
#include <string.h>
#include <queue>
#include <map>

using namespace std;

typedef set<Node*>::const_iterator node_iterator;
class Graph {
	std::set<Node*> nodes;
public:
	void addNode(Node* node);
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end);
	void removeEdge(Node* begin, Node* end);
	node_iterator begin() const {
		return nodes.begin();
	}
	node_iterator end() const { return nodes.end(); }
};

class Node {
	std::string name;
	std::set<Node*> neighbours;
	void addNeighbour(Node* neighbour);
	void removeNeighbour(Node* neighbour);
public:
	Node(const std::string& aname) : name(aname) {}
	const std::string& getName() const { return name; }
	node_iterator nb_begin() const {
		return neighbours.begin();
	}
	node_iterator nb_end() const { return neighbours.end(); }
	friend class Graph;
};
class BFS {
	const Graph& graph;
public:
	BFS(const Graph& agraph) : graph(agraph) {}
	bool connected(Node* begin, Node* end);
};

struct MarkedNode {
	Node* node; int mark;
	Node* prev;
	MarkedNode(Node* anode = 0, int amark = 0, Node* aprev = 0) :
		node(anode), mark(amark), prev(aprev) {}
};
class PriorityQueue {
	std::vector<MarkedNode> nodes;
public:
	MarkedNode pop();
	void push(Node* node, int mark, Node* prev);
	bool empty() const { return nodes.empty(); }
};MarkedNode PriorityQueue::pop() {
	MarkedNode mn = nodes.back();
	nodes.pop_back();
	return mn;
}
void PriorityQueue::push(Node* node, int mark, Node* prev) {
	std::vector<MarkedNode>::iterator it = nodes.begin();
	MarkedNode mn(node, mark, prev);
	// From higher to lower
	while (it != nodes.end() && mark < it->mark) it++;
	if (it == nodes.end()) nodes.push_back(mn);
	else nodes.insert(it, mn);
}

struct Way {
	std::vector<Node*> nodes;
	int length;
	Way() : length(-1) {}
};
class Dijkstra {
	const Graph& graph;
public:
	Dijkstra(const Graph& agraph) : graph(agraph) {}
	Way shortestWay(Node* begin, Node* end);
};


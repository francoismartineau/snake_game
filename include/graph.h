#ifndef GRAPH_H
#define GRAPH_H

#include <deque>
#include <list>
#include <stack>
#include <limits>
#include <iostream>
#include <algorithm>
#include "wall.h"

#define MAX_LENGTH 9360

class Graph
{
public:

	Graph(size_t p_nbSommets = 0, size_t width = 0);
    void resize(size_t);
	void addEdge(size_t i, size_t j, unsigned int weight);
	bool hasEdge(size_t i, size_t j);
	void removeEdge(size_t i, size_t j);
	void setIsOccupied(size_t i, bool occupied);
	unsigned int getWeight(size_t i, size_t j) const;
	void setWeight(size_t i, size_t j, unsigned int weight);
	size_t getNodesQty() const;
    size_t getEdgesQty() const;

	bool reachable(size_t ori, size_t goal);
    unsigned int shortestPath(size_t start, size_t goal,
                             std::deque<size_t> & path) const;
	size_t areaSize(size_t origin);

	struct Edge
	{
		Edge(size_t dest, unsigned int p);
		size_t destination;
		unsigned int weight;
		bool operator==(const Edge& other) const;
	};

	struct Node
	{
		Node();
		bool occupied;
		size_t weigth;
		std::list<Edge> edges;
	};
	std::vector<Node> nodes;
	
private:
	// std::vector<std::list<Edge> > m_listesAdj; /*!< les listes d'adjacence */
    size_t maxPathLength() const;
	unsigned long edgesQty;
    void makePath(const size_t& start, const size_t& goal, const std::vector<size_t>& predecessor, std::deque<size_t> &path) const;
	void relaxation(const size_t& current, std::list<size_t> queue[], std::vector<unsigned int>& distance, std::vector<size_t>& predecessor, unsigned int& maxDistEverSeen) const;
	size_t _areaSize(size_t origin, std::vector<bool> &visited);
	void _reachable(size_t ori, size_t goal, bool *reachable, std::vector<bool> &visited);
	size_t width;
};

#endif  //GRAPH_H

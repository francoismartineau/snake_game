//
//  Graph.h
//  Classe pour graphes orientés pondérés (non négativement) avec listes d'adjacence
//
//  Mario Marchand automne 2016.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
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
	void ajouterArc(size_t i, size_t j, unsigned int weight);
	bool hasArc(size_t i, size_t j);
	void enleverArc(size_t i, size_t j);
	void setIsOccupied(size_t i, bool occupied);
	unsigned int getWeight(size_t i, size_t j) const;
	void setWeight(size_t i, size_t j, unsigned int weight);
	size_t getNbSommets() const;
    size_t getNbArcs() const;

	bool reachable(size_t ori, size_t goal);
    unsigned int plusCourtChemin(size_t p_origine, size_t p_destination,
                             std::vector<size_t> & p_chemin) const;
	size_t areaSize(size_t origin);

private:

	struct Arc
	{
		Arc(size_t dest, unsigned int p);
		size_t destination;
		unsigned int weight;
		bool operator==(const Arc& other) const;
	};

	struct Node
	{
		Node();
		bool occupied;
		std::list<Arc> edges;
	};
	std::vector<Node> nodes;

	// std::vector<std::list<Arc> > m_listesAdj; /*!< les listes d'adjacence */
    // size_t getQueueSize() const;
	unsigned long nbArcs;
    void makePath(const size_t& p_origine, const size_t& p_destination, const std::vector<size_t>& predecesseur, std::vector<size_t> &p_chemin) const;
	void relaxation(const size_t& current, std::list<size_t> queue[], std::vector<unsigned int>& distance, std::vector<size_t>& predecesseur, unsigned int& maxDistEverSeen) const;
	size_t _areaSize(size_t origin, std::vector<bool> &visited);
	void _reachable(size_t ori, size_t goal, bool *reachable, std::vector<bool> &visited);
	size_t width;
};

#endif  //GRAPH_H

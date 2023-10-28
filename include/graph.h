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

#define MAX_LENGTH 9360

//! \brief  Classe pour graphes orientés pondérés (non négativement) avec listes d'adjacence
class Graph
{
public:

	Graph(size_t = 0);
    void resize(size_t);
	void ajouterArc(size_t i, size_t j, unsigned int weight);
	bool hasArc(size_t i, size_t j);
	void enleverArc(size_t i, size_t j);
	unsigned int getWeight(size_t i, size_t j) const;
	void setWeight(size_t i, size_t j, unsigned int weight);
	size_t getNbSommets() const;
    size_t getNbArcs() const;

    unsigned int plusCourtChemin(size_t p_origine, size_t p_destination,
                             std::vector<size_t> & p_chemin) const;

private:

	struct Arc
	{
		Arc(size_t dest, unsigned int p);
		size_t destination;
		unsigned int weight;
		bool operator==(const Arc& other) const;
	};


	std::vector<std::list<Arc> > m_listesAdj; /*!< les listes d'adjacence */
    // size_t getQueueSize() const;
	unsigned long nbArcs;
    void makePath(const size_t& p_origine, const size_t& p_destination, const std::vector<size_t>& predecesseur, std::vector<size_t> &p_chemin) const;
	void relaxation(const size_t& current, std::list<size_t> queue[], std::vector<unsigned int>& distance, std::vector<size_t>& predecesseur, unsigned int& maxDistEverSeen) const;
};

#endif  //GRAPH_H

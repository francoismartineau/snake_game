//
//  Graph.cpp
//  Classe pour graphs orientés pondérés (non négativement) avec listes d'adjacence
//
//  Mario Marchand automne 2016.
//

#include "graph.h"

using namespace std;


Graph::Graph(size_t p_nbSommets, size_t width)
    : nodes(p_nbSommets), nbArcs(0), width(width)
{
}

void Graph::resize(size_t p_nouvelleTaille)
{
    nodes.resize(p_nouvelleTaille);
}

size_t Graph::getNbSommets() const
{
	return nodes.size();
}

size_t Graph::getNbArcs() const
{
    return nbArcs;
}

void Graph::ajouterArc(size_t i, size_t j, unsigned int weight)
{
    if (i >= nodes.size())
        throw logic_error("Graph::ajouterArc(): tentative d'ajouter l'arc(i,j) avec un sommet i inexistant");
    if (j >= nodes.size())
        throw logic_error("Graph::ajouterArc(): tentative d'ajouter l'arc(i,j) avec un sommet j inexistant");
    if (!this->hasArc(i, j))
        nodes[i].edges.emplace_back(Arc(j, weight));
    ++nbArcs;
}

bool Graph::hasArc(size_t i, size_t j)
{
    auto it = std::find(nodes[i].edges.begin(), nodes[i].edges.end(), Arc(j, 0));
    return it != nodes[i].edges.end();
}

void Graph::enleverArc(size_t i, size_t j)
{
    if (i >= nodes.size())
        throw logic_error("Graph::enleverArc(): tentative d'enlever l'arc(i,j) avec un sommet i inexistant");
    if (j >= nodes.size())
        throw logic_error("Graph::enleverArc(): tentative d'enlever l'arc(i,j) avec un sommet j inexistant");
    auto &liste = nodes[i].edges;
    bool arc_enleve = false;
    for (auto itr = liste.end(); itr != liste.begin();) //on débute par la fin par choix
    {
        if ((--itr)->destination == j)
        {
            liste.erase(itr);
            arc_enleve = true;
            break;
        }
    }
    if (arc_enleve)
        --nbArcs;
}

void Graph::setIsOccupied(size_t i, bool occupied)
{
    nodes[i].occupied = occupied;
}


unsigned int Graph::getWeight(size_t i, size_t j) const
{
    if (i >= nodes.size()) throw logic_error("Graph::getWeight(): l'incice i n,est pas un sommet existant");
    for (auto & arc : nodes[i].edges)
    {
        if (arc.destination == j)
            return arc.weight;
    }
    throw logic_error("Graph::getWeight(): l'arc(i,j) est inexistant");
}

void Graph::setWeight(size_t i, size_t j, unsigned int weight)
{
    if (i >= nodes.size()) throw logic_error("Graph::getWeight(): l'incice i n,est pas un sommet existant");
    for (auto & arc : nodes[i].edges)
    {
        if (arc.destination == j)
        {
            arc.weight = weight;
            return;
        }
    }
    throw logic_error("Graph::getWeight(): l'arc(i,j) est inexistant");
}

unsigned int Graph::plusCourtChemin(size_t start, size_t goal, deque<size_t> &path) const
{
    if (start >= nodes.size() || goal >= nodes.size())
        throw logic_error("Graph::dijkstra(): start ou goal n'existe pas");

    if (start == goal)
        return 0;

    // Initialisation des conteneurs
    size_t queue_size = MAX_LENGTH;//la somme du poids des arcs//;MAX_LENGTH;
    list<size_t> queue[queue_size];
    queue[0].push_front(start);
    size_t lowerBound = 0;
    vector<unsigned int> distance(getNbSommets(), numeric_limits<unsigned int>::max());
    distance[start] = 0;
    vector<size_t> predecesseur(getNbSommets(), numeric_limits<size_t>::max());
    unsigned int maxDistEverSeen = 0;
    size_t current;

    // Départ
    while (true)
    {
        while (queue[lowerBound].size() == 0)
            if (++lowerBound > maxDistEverSeen) return numeric_limits<unsigned int>::max();
        current = queue[lowerBound].front();
        queue[lowerBound].pop_front();
        if (current == goal)
        {
            makePath(start, goal, predecesseur, path);
            return distance[goal];
        }
        relaxation(current, queue, distance, predecesseur, maxDistEverSeen);
    }
}

// size_t Graph::getQueueSize() const
// {
//     size_t size = 0;

//     for (const std::list<Arc>& arcList : m_listesAdj)
//         for (const Arc& arc : arcList)
//             size += arc.weight;
//     return size;
// }


void Graph::makePath(const size_t& start, const size_t& goal, const vector<size_t>& predecesseur, deque<size_t> &path) const
{
    for (size_t current = goal; current != start; current = predecesseur[current])
        path.push_front(current);
}

void Graph::relaxation(const size_t& current, list<size_t> queue[], vector<unsigned int>& distance, vector<size_t>& predecesseur, unsigned int& maxDistEverSeen) const
{
    for (const Arc& edge : nodes[current].edges)
    {
        const size_t& neighbor = edge.destination;
        unsigned int test_distance = distance[current] + edge.weight;
        if (test_distance < distance[neighbor])
        {
            if (distance[neighbor] < numeric_limits<unsigned int>::max())
                queue[distance[neighbor]].remove(neighbor);
            queue[test_distance].push_front(neighbor);
            distance[neighbor] = test_distance;
            predecesseur[neighbor] = current;
            if (maxDistEverSeen < test_distance)
                maxDistEverSeen = test_distance;
        }
    }
}

bool Graph::reachable(size_t ori, size_t goal)
{
    Position goalPos = indexToPos(goal, this->width);
    bool res = false;
    std::vector<Direction> directions = {LEFT, UP, RIGHT, DOWN, LEFT_UP, RIGHT_UP , RIGHT_DOWN, LEFT_DOWN};
    for (auto dir: directions)
    {
        Position neighbor = goalPos.neighbor(dir, 1);
        size_t currGoal = posToIndex(neighbor, this->width);
        if (currGoal < nodes.size()
            && nodes[currGoal].occupied)
            continue;
        std::vector<bool> visited(nodes.size(), false);
        _reachable(ori, currGoal, &res, visited);
        if (res)
            break;
    }
    return res;
}

void Graph::_reachable(size_t ori, size_t goal, bool *reachable, std::vector<bool> &visited)
{

    if (visited[ori] || *reachable)
        return;

    visited[ori] = true;
    for (auto &edge: nodes[ori].edges)
    {
        if (edge.destination == goal)
        {
            *reachable = true;
            return;
        }
        _reachable(edge.destination, goal, reachable, visited);
        if (*reachable == true)
            return;
    }
}

size_t Graph::areaSize(size_t ori)
{
    std::vector<bool> visited(nodes.size(), false);
    return _areaSize(ori, visited);
    
}

size_t Graph::_areaSize(size_t ori, std::vector<bool> &visited)
{
    if (visited[ori])
        return 0;

    visited[ori] = true;
    size_t regionSize = 1;
    for (auto &edge: nodes[ori].edges)
        regionSize += _areaSize(edge.destination, visited);
    return regionSize;
}


Graph::Arc::Arc(size_t dest, unsigned int p)
    : destination(dest), weight(p)
{
}

bool Graph::Arc::operator==(const Arc& other) const
{
	return destination == other.destination;
}

Graph::Node::Node()
    : occupied(0)
{
}

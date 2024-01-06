#include "graphDijkstra.h"

using namespace std;


Graph::Graph(size_t p_nbSommets, size_t width)
    : nodes(p_nbSommets), edgesQty(0), width(width)
{
}

void Graph::resize(size_t p_nouvelleTaille)
{
    nodes.resize(p_nouvelleTaille);
}

size_t Graph::getNodesQty() const
{
	return nodes.size();
}

size_t Graph::getEdgesQty() const
{
    return edgesQty;
}

void Graph::addEdge(size_t i, size_t j, unsigned int weight)
{
    if (i >= nodes.size())
        throw logic_error("Graph::addEdge(): index i isn't an existing node.");
    if (j >= nodes.size())
        throw logic_error("Graph::addEdge(): index j isn't an existing node.");
    if (!this->hasEdge(i, j))
        nodes[i].edges.emplace_back(Edge(j, weight));
    ++edgesQty;
}

bool Graph::hasEdge(size_t i, size_t j)
{
    auto it = std::find(nodes[i].edges.begin(), nodes[i].edges.end(), Edge(j, 0));
    return it != nodes[i].edges.end();
}

void Graph::removeEdge(size_t i, size_t j)
{
    if (i >= nodes.size())
        throw logic_error("Graph::removeEdge(): index i isn't an existing node.");
    if (j >= nodes.size())
        throw logic_error("Graph::removeEdge(): index j isn't an existing node.");
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
        --edgesQty;
}

void Graph::setIsOccupied(size_t i, bool occupied)
{
    nodes[i].occupied = occupied;
}


unsigned int Graph::getWeight(size_t i, size_t j) const
{
    if (i >= nodes.size()) throw logic_error("Graph::getWeight(): index i isn't an existing node.");
    for (auto & edge : nodes[i].edges)
    {
        if (edge.destination == j)
            return edge.weight;
    }
    throw logic_error("Graph::getWeight(): edge(i,j) doesn't exist");
}

void Graph::setWeight(size_t i, size_t j, unsigned int weight)
{
    if (i >= nodes.size()) throw logic_error("Graph::getWeight(): index i isn't an existing node.");
    for (auto & edge : nodes[i].edges)
    {
        if (edge.destination == j)
        {
            edge.weight = weight;
            return;
        }
    }
    throw logic_error("Graph::getWeight(): edge(i,j) doesn't exist");
}

unsigned int Graph::shortestPath(size_t start, size_t goal, deque<size_t> &path) const
{
    if (start >= nodes.size() || goal >= nodes.size())
        throw logic_error("Graph::dijkstra(): start or goal doesn't exist");

    if (start == goal)
        return 0;

    // init
    size_t queue_size = this->maxPathLength();
    list<size_t> queue[queue_size];
    queue[0].push_front(start);
    size_t lowerBound = 0;
    vector<unsigned int> distance(getNodesQty(), numeric_limits<unsigned int>::max());
    distance[start] = 0;
    vector<size_t> predecessor(getNodesQty(), numeric_limits<size_t>::max());
    unsigned int maxDistEverSeen = 0;
    size_t current;

    // start
    while (true)
    {
        while (queue[lowerBound].size() == 0)
            if (++lowerBound > maxDistEverSeen) return numeric_limits<unsigned int>::max();
        current = queue[lowerBound].front();
        queue[lowerBound].pop_front();
        if (current == goal)
        {
            makePath(start, goal, predecessor, path);
            return distance[goal];
        }
        relaxation(current, queue, distance, predecessor, maxDistEverSeen);
    }
}



size_t Graph::maxPathLength() const
{
    size_t len = 0;

    for (const Node& node : nodes)
        for (const Edge& edge : node.edges)
            len += edge.weight;
    return len;
}


void Graph::makePath(const size_t& start, const size_t& goal, const vector<size_t>& predecessor, deque<size_t> &path) const
{
    for (size_t current = goal; current != start; current = predecessor[current])
        path.push_front(current);
}

void Graph::relaxation(const size_t& current, list<size_t> queue[], vector<unsigned int>& distance, vector<size_t>& predecessor, unsigned int& maxDistEverSeen) const
{
    for (const Edge& edge : nodes[current].edges)
    {
        const size_t& neighbor = edge.destination;
        unsigned int test_distance = distance[current] + edge.weight;
        if (test_distance < distance[neighbor])
        {
            if (distance[neighbor] < numeric_limits<unsigned int>::max())
                queue[distance[neighbor]].remove(neighbor);
            queue[test_distance].push_front(neighbor);
            distance[neighbor] = test_distance;
            predecessor[neighbor] = current;
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


Graph::Edge::Edge(size_t dest, unsigned int p)
    : destination(dest), weight(p)
{
}

bool Graph::Edge::operator==(const Edge& other) const
{
	return destination == other.destination;
}

Graph::Node::Node()
    : occupied(0)
{
}

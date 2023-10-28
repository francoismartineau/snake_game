//
//  Graph.cpp
//  Classe pour graphs orientés pondérés (non négativement) avec listes d'adjacence
//
//  Mario Marchand automne 2016.
//

#include "graph.h"

using namespace std;

//! \brief Constructeur avec paramètre du nombre de sommets désiré
//! \param[in] p_nbSommets indique le nombre de sommets désiré
//! \post crée le vecteur de p_nbSommets de listes d'adjacence vides
Graph::Graph(size_t p_nbSommets)
    : m_listesAdj(p_nbSommets), nbArcs(0)
{
}

//! \brief change le nombre de sommets du graph
//! \param[in] p_nouvelleTaille indique le nouveau nombre de sommet
//! \post le graph est un vecteur de p_nouvelleTaille de listes d'adjacence
//! \post les anciennes listes d'adjacence sont toujours présentes lorsque p_nouvelleTaille >= à l'ancienne taille
//! \post les dernières listes d'adjacence sont enlevées lorsque p_nouvelleTaille < à l'ancienne taille
void Graph::resize(size_t p_nouvelleTaille)
{
    m_listesAdj.resize(p_nouvelleTaille);
}

size_t Graph::getNbSommets() const
{
	return m_listesAdj.size();
}

size_t Graph::getNbArcs() const
{
    return nbArcs;
}

//! \brief ajoute un arc d'un weight donné dans le graph
//! \param[in] i: le sommet origine de l'arc
//! \param[in] j: le sommet destination de l'arc
//! \param[in] weight: le weight de l'arc
//! \pre les sommets i et j doivent exister
//! \throws logic_error lorsque le sommet i ou le sommet j n'existe pas
//! \throws logic_error lorsque le weight == numeric_limits<unsigned int>::max()
void Graph::ajouterArc(size_t i, size_t j, unsigned int weight)
{
    if (i >= m_listesAdj.size())
        throw logic_error("Graph::ajouterArc(): tentative d'ajouter l'arc(i,j) avec un sommet i inexistant");
    if (j >= m_listesAdj.size())
        throw logic_error("Graph::ajouterArc(): tentative d'ajouter l'arc(i,j) avec un sommet j inexistant");
    if (!this->hasArc(i, j))
        m_listesAdj[i].emplace_back(Arc(j, weight));
    ++nbArcs;
}

bool Graph::hasArc(size_t i, size_t j)
{
    auto it = std::find(m_listesAdj[i].begin(), m_listesAdj[i].end(), Arc(j, 0));
    return it != m_listesAdj[i].end();
}

//! \brief enlève un arc dans le graph
//! \param[in] i: le sommet origine de l'arc
//! \param[in] j: le sommet destination de l'arc
//! \pre l'arc (i,j) et les sommets i et j dovent exister
//! \post enlève l'arc mais n'enlève jamais le sommet i
//! \throws logic_error lorsque le sommet i ou le sommet j n'existe pas
//! \throws logic_error lorsque l'arc n'existe pas
void Graph::enleverArc(size_t i, size_t j)
{
    if (i >= m_listesAdj.size())
        throw logic_error("Graph::enleverArc(): tentative d'enlever l'arc(i,j) avec un sommet i inexistant");
    if (j >= m_listesAdj.size())
        throw logic_error("Graph::enleverArc(): tentative d'enlever l'arc(i,j) avec un sommet j inexistant");
    auto &liste = m_listesAdj[i];
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

unsigned int Graph::getWeight(size_t i, size_t j) const
{
    if (i >= m_listesAdj.size()) throw logic_error("Graph::getWeight(): l'incice i n,est pas un sommet existant");
    for (auto & arc : m_listesAdj[i])
    {
        if (arc.destination == j)
            return arc.weight;
    }
    throw logic_error("Graph::getWeight(): l'arc(i,j) est inexistant");
}

void Graph::setWeight(size_t i, size_t j, unsigned int weight)
{
    if (i >= m_listesAdj.size()) throw logic_error("Graph::getWeight(): l'incice i n,est pas un sommet existant");
    for (auto & arc : m_listesAdj[i])
    {
        if (arc.destination == j)
        {
            arc.weight = weight;
            return;
        }
    }
    throw logic_error("Graph::getWeight(): l'arc(i,j) est inexistant");
}

//! \brief Algorithme de Dijkstra permettant de trouver le plus court chemin entre p_origine et p_destination
//! \pre p_origine et p_destination doivent être des sommets du graph
//! \return la longueur du plus court chemin est retournée
//! \param[out] le chemin est retourné (un seul noeud si p_destination == p_origine ou si p_destination est inatteignable)
//! \return la longueur du chemin (= numeric_limits<unsigned int>::max() si p_destination n'est pas atteignable)
//! \throws logic_error lorsque p_origine ou p_destination n'existe pas
unsigned int Graph::plusCourtChemin(size_t p_origine, size_t p_destination, vector<size_t> &p_chemin) const
{
    if (p_origine >= m_listesAdj.size() || p_destination >= m_listesAdj.size())
        throw logic_error("Graph::dijkstra(): p_origine ou p_destination n'existe pas");

    if (p_origine == p_destination)
    {
        p_chemin.push_back(p_destination);
        return 0;
    }

    // Initialisation des conteneurs
    // std::cout << this->getQueueSize() << std::endl;
    size_t queue_size = MAX_LENGTH;//la somme du poids des arcs//;MAX_LENGTH;
    list<size_t> queue[queue_size];
    queue[0].push_front(p_origine);
    size_t lowerBound = 0;
    vector<unsigned int> distance(getNbSommets(), numeric_limits<unsigned int>::max());
    distance[p_origine] = 0;
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

        if (current == p_destination)
        {
            makePath(p_origine, p_destination, predecesseur, p_chemin);
            return distance[p_destination];
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



//! \brief Cette méthode privée est appelée par plusCourtChemin et permet de créer le plus court
//! \brief chemin à partir des prédécesseurs de chaque noeud
//! \param[in] p_origine: le sommet d'origine
//! \param[in] p_destination: le sommet de destination
//! \param[in] predecesseurs: la liste des prédécesseurs pour chaque noeud
//! \param[in] p_chemin: le conteneur qui contiendra le plus court chemin résultant
void Graph::makePath(const size_t& p_origine, const size_t& p_destination, const vector<size_t>& predecesseur, vector<size_t> &p_chemin) const
{
    size_t current = p_destination;
    p_chemin.push_back(current);
    do
    {
        current = predecesseur[current];
        p_chemin.push_back(current);
    } while (current != p_origine);
    reverse(p_chemin.begin(), p_chemin.end());
}

//! \brief Cette méthode privée est appelée par plusCourtChemin et permet d'éventuellement relaxer
//! \brief la distance estimée des voisins du noeud passé
//! \param[in] current: le sommet courant
//! \param[in] distance: les distances estimées pour tous les sommets
//! \param[in] predecesseurs: les prédécesseurs pour tous les sommets
//! \param[in] maxDistEverSeen: l'indice de la dernière cellule utilisée dans queue
void Graph::relaxation(const size_t& current, list<size_t> queue[], vector<unsigned int>& distance, vector<size_t>& predecesseur, unsigned int& maxDistEverSeen) const
{
    for (const Arc& edge : m_listesAdj[current])
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

Graph::Arc::Arc(size_t dest, unsigned int p)
    : destination(dest), weight(p)
{
}

bool Graph::Arc::operator==(const Arc& other) const
{
	return destination == other.destination;
}

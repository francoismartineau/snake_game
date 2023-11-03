#include <iostream>
#include <ctime>
#include <cstdlib>
#include "game.h"
#include "graph.h"


void composeGraph(Graph &graph, const Wall &wall)
{
    size_t i;

    for (size_t x = 0; x < wall.width; ++x)
    {
        for (size_t y = 0; y < wall.height; ++y)
        {
            i = coordToIndex(x, y, wall.width);
            if (x > 0)
                graph.ajouterArc(i, coordToIndex(x-1, y, wall.width), 1);
            if (x < wall.width - 1)
                graph.ajouterArc(i, coordToIndex(x+1, y, wall.width), 1);
            if (y > 0)
                graph.ajouterArc(i, coordToIndex(x, y-1, wall.width), 1);
            if (y < wall.height - 1)
                graph.ajouterArc(i, coordToIndex(x, y+1, wall.width), 1);
        }
    }
}

int main(int argc, char **argv)
{
    std::srand(time(NULL));
    if (argc != 2)
    {
        std::cout << "No wall file provided." << std::endl;
        return 1;
    }
    Wall wall = Wall(argv[1]);
    Graph graph(wall.width * wall.height, wall.width);
    composeGraph(graph, wall);
    Snake snake = Snake(2, wall.height-2, 2, RIGHT);
    std::cout << "Game start..." << std::endl;
    Game game(&wall, &snake, &graph);
    return 0;
}

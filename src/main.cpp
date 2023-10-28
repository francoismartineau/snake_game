#include <iostream>
#include "Game.h"
#include "graph.h"

Graph *createGraph(Wall *wall)
{
    Graph *graph;
    size_t i;

    graph = new Graph(wall->width * wall->height);
    for (size_t x = 0; x < wall->width; ++x)
    {
        for (size_t y = 0; y < wall->height; ++y)
        {
            i = coordToIndex(x, y, wall->width);
            if (x > 0)
                graph->ajouterArc(i, coordToIndex(x-1, y, wall->width), 1);
            if (x < wall->width - 1)
                graph->ajouterArc(i, coordToIndex(x+1, y, wall->width), 1);
            if (y > 0)
                graph->ajouterArc(i, coordToIndex(x, y-1, wall->width), 1);
            if (y < wall->height - 1)
                graph->ajouterArc(i, coordToIndex(x, y+1, wall->width), 1);
        }
    }
    return graph;
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "No wall file provided." << std::endl;
        return 1;
    }
    Wall *wall = new Wall(argv[1]);
    Graph *graph = createGraph(wall);
    Snake *snake = new Snake(2, wall->height-2, 2, RIGHT);
    std::cout << "Game start..." << std::endl;
    Game game(wall, snake, graph);
    delete wall;
    delete snake;
    delete graph;
    return 0;
}

#include <conio.h>
#include <Windows.h>
#include <synchapi.h>
#include <limits>
#include <algorithm>
#include <random>
#include <vector>
#include <thread>
#include "Game.h"
#include "apple.h"
#include "define.h"

Game::Game(Wall *wall, Snake *snake, Graph *graph)
    : wall(wall),
    snake(snake),
    graph(graph),
    apple(new Apple),
    speed(1),
    growSpeed(1)
{
    this->snake->reset(this->wall->width, this->wall->height);
    this->apple->place(this->wall, this->snake);
    dijkstraSnake();
    // userSnake();
}

void Game::dijkstraSnake()
{
    while (true)
    {
        this->updateGraph();
        std::vector<size_t> path;
        size_t start = posToIndex(this->snake->getHeadPos(), this->wall->width);
        size_t goal = posToIndex(this->apple->pos, this->wall->width);
        bool goalInReach = (this->graph->plusCourtChemin(start, goal, path)
            != std::numeric_limits<unsigned int>::max());
        if (!goalInReach)
        {
            this->tick(this->survive(this->snake->getHeadPos()));
            continue ;
        }
        Position next_pos = indexToPos(path[1], this->wall->width);
        enum Direction dir = this->getDir(this->snake->getHeadPos(), next_pos);
        this->tick(dir);
    }
}

Direction Game::getDir(Position from, Position to)
{
    enum Direction dir = NONE;
    if (to.y == from.y + this->speed)
        dir = DOWN; 
    else if (to.y == from.y - this->speed)
        dir = UP;
    else if (to.y < from.y)
        dir = DOWN; 
    else if (to.y > from.y)
        dir = UP; 
    else if (to.x == from.x + this->speed)
        dir = RIGHT; 
    else if (to.x == from.x - this->speed)
        dir = LEFT;
    else if (to.x < from.x)
        dir = RIGHT; 
    else if (to.x > from.x)
        dir = LEFT;     
    return dir;   
}

void Game::userSnake()
{
    while (true)
    {
        if(_kbhit())
            this->tick(keyInput());
        else
            this->tick(NONE);
    }
}

void Game::infiniteSnake()
{
    size_t yTop = 2;
    size_t yBottom = this->wall->height-2;
    size_t xRight = this->wall->width-1;
    size_t xLeft = 2;
    size_t y = this->wall->height-3;

    while(true)
    {
        while (true)
        {
            if (this->snake->getHeadPos().y != yTop)
            {
                do
                {
                    this->tick(UP);
                }
                while (this->snake->getHeadPos().y > yTop);    
            }
            else
            {
                do
                {
                    this->tick(DOWN);
                }
                while (this->snake->getHeadPos().y < yBottom);
            }
            if (this->snake->getHeadPos().x < xRight - 1)
                this->tick(RIGHT);
            else
                break;
        }
        this->tick(UP);
        do
        {
            this->tick(LEFT);
        }
        while (this->snake->getHeadPos().x >= xLeft);
        do
        {
            this->tick(DOWN);
            ++y;
        }
        while (this->snake->getHeadPos().y < yBottom);
        this->tick(RIGHT);
    }
}

void Game::tick()
{
    this->tick(this->snake->dir);
}

void Game::tick(Direction dir)
{
    this->takeFrameTime();
    std::cout << "dir: " << dir << std::endl;
    this->snake->move(dir); 
    this->updateGraph();
    if (collision())
        collide();
    else if (!this->apple->hidden &&
        this->apple->pos == this->snake->getBlocPos(0))
    {
        this->snake->grow(this->growSpeed);
        this->apple->place(this->wall, this->snake);
    }
    this->draw();
    this->fpsSync();
}

// TODO: regarder la map intelligemment en devinant et en isolant les changements
//  si mange pomme, flag position noeud final
//  si meurt, tout refaire
//  premier (selon dir) et dernier morceau de serpent

// si diff x ou diff y != speed, dir = reverse(dir)
void Game::updateGraph()
{
    for (size_t x = 0; x < this->wall->width; ++x)
    {
        for (size_t y = 0; y < this->wall->height; ++y)
        {
            if (this->snake->overlap(Position(x, y))
                || this->wall->overlap(Position(x, y)))
                this->removeArcsToNode(x, y);
            else
                this->addArcsToNode(x, y);
        }
    }
}

void Game::addArcsToNode(size_t x, size_t y)
{
    std::vector<std::pair<size_t, size_t>> nodes = {{x-1, y}, {x, y-1}, {x+1, y}, {x, y+1}};
    for (const auto& node : nodes)
    {
        size_t adjacent_x = node.first;
        size_t adjacent_y = node.second;
        if (adjacent_x == ((size_t) -1))
            adjacent_x = this->wall->width - 1;
        else if (adjacent_y == ((size_t) -1))
            adjacent_y = this->wall->height - 1;
        else if (adjacent_x == this->wall->width)
            adjacent_x = 0;
        else if (adjacent_y == this->wall->height)
            adjacent_y = 0;
        // bool outOfBounds = (adjacent_x <= 0 || adjacent_x >= this->wall->width - 1
        //     || adjacent_y <= 0 || adjacent_y >= this->wall->height - 1);
        // if (outOfBounds)
        //     continue;
        size_t thisNode = coordToIndex(x, y, this->wall->width);
        size_t adjacentNode = coordToIndex(adjacent_x, adjacent_y, this->wall->width);
        this->graph->ajouterArc(adjacentNode, thisNode, 1);
    }
}

void Game::removeArcsToNode(size_t x, size_t y)
{
    std::vector<std::pair<size_t, size_t>> nodes = {{x-1, y}, {x, y-1}, {x+1, y}, {x, y+1}};
    for (const auto& node : nodes)
    {
        size_t adjacent_x = node.first;
        size_t adjacent_y = node.second;
        if (adjacent_x == ((size_t) -1))
            adjacent_x = this->wall->width - 1;
        else if (adjacent_y == ((size_t) -1))
            adjacent_y = this->wall->height - 1;
        else if (adjacent_x == this->wall->width)
            adjacent_x = 0;
        else if (adjacent_y == this->wall->height)
            adjacent_y = 0;
        size_t thisNode = coordToIndex(x, y, this->wall->width);
        size_t adjacentNode = coordToIndex(adjacent_x, adjacent_y, this->wall->width);
        this->graph->enleverArc(adjacentNode, thisNode);
    }
}

Direction Game::survive(Position headPos)
{
    size_t x = headPos.x;
    size_t y = headPos.y;
    std::vector<std::pair<size_t, size_t>> nodes = {{x-1, y}, {x, y-1}, {x+1, y}, {x, y+1}};
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(nodes.begin(), nodes.end(), gen);
    for (const auto& node : nodes)
    {
        size_t adjacent_x = node.first;
        size_t adjacent_y = node.second;
        bool outOfBounds = (adjacent_x <= 0 || adjacent_x >= this->wall->width - 1
            || adjacent_y <= 0 || adjacent_y >= this->wall->height - 1);
        if (outOfBounds)
            continue;
        size_t thisNode = coordToIndex(x, y, this->wall->width);
        size_t adjacentNode = coordToIndex(adjacent_x, adjacent_y, this->wall->width);
        if (this->graph->hasArc(thisNode, adjacentNode))
            return this->getDir(Position(x, y), Position(adjacent_x, adjacent_y));
    }
    return NONE;
}

Game::~Game()
{
  delete this->apple;
  delete this->wall;
  delete this->snake;
}

Direction Game::keyInput()
{
    char current = _getch();
    switch (current)
    {
    case 'i':
        return UP;
    case 'j':
        return LEFT;
    case 'k':
        return DOWN;
    case 'l':
        return RIGHT;
    }
    return NONE;
}

bool Game::collision()
{
    if (this->wall->overlap(this->snake->getHeadPos()))
        return true;
      
    for(size_t i = 1; i < this->snake->getLength(); ++i)
    {
        if(snake->getHeadPos() == snake->getBlocPos(i))
            return true;
    }
    return false;
}

void Game::collide()
{
    std::cout << "Collision!" << std::endl;
    Sleep(3000);
    this->snake->reset(this->wall->width, this->wall->height);
    this->apple->place(this->wall, this->snake);    
}

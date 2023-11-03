#include <conio.h>
#include <Windows.h>
#include <synchapi.h>
#include <limits>
#include <random>
#include <vector>
#include <algorithm>
#include <thread>
#include "game.h"
#include "apple.h"
#include "define.h"
#include "util.h"
#include "util.h"

Game::Game(Wall *wall, Snake *snake, Graph *graph)
    : wall(wall),
    snake(snake),
    graph(graph),
    apple(new Apple),
    fps(FPS),
    speed(1),
    growSpeed(GROW_SPEED)
{
    this->snake->reset(this->wall->width, this->wall->height);
    this->apple->place(this->wall, this->snake);
    gameChoice();
    // userSnake();
}

void Game::gameChoice()
{
    const std::string prompt = "[1] user snake\n"
        "[2] dijkstra snake\n"
        "[3] invincible user snake\n"
        "[4] quit";
    int choice;
    bool quit = false;
    while (!quit)
    {
        std::cout << prompt << std::endl;
        std::cin >> choice;
        switch (choice)
        {
            case 1:
                this->userSnake(false);
            case 2:
                this->dijkstraSnake();
                break;
            case 3:
                this->userSnake(true);
                break;
            case 4:
                quit = true;
                break;
            default:
                std::cout << "Invalid choice. Please enter 1, 2, or 3." << std::endl;
                break;
        }
    }
}

void Game::userSnake(bool survive)
{
    Direction dir;


    while (true)
    {
        if(_kbhit())
            dir = keyInput();
        else
            dir = this->snake->dir;
        if (survive)
            dir = this->survive(dir);
        this->tick(dir);
    }
}

Direction Game::survive(Direction dir)
{
    static Direction prevSeenDir = NONE;
    static Direction prevDir = NONE;

    std::vector<Direction> dirs = dirsAvailable();
    bool alreadySurvives = dirs.size() != 0
        && std::find(dirs.begin(), dirs.end(), dir) != dirs.end();
    if (!alreadySurvives)
    {
        bool prevDirSurvives = dirs.size() != 0
            && std::find(dirs.begin(), dirs.end(), prevDir) != dirs.end();
        if (prevDirSurvives)
            dir = prevDir;
        else
        {
            shuffleVector(dirs);
            dir = dirs[0];
        }
    }
    if (prevSeenDir != dir)
        prevDir = prevSeenDir;
    prevSeenDir = dir;
    return dir;  
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

void Game::freezeFrame()
{
    this->takeFrameTime();
    this->draw();
    this->fpsSync();   
}

void Game::tick()
{
    this->tick(this->snake->dir);
}

void Game::tick(Direction dir)
{
    this->takeFrameTime();
    // std::cout << "dir: " << dir << std::endl;
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
    Position pos;
    for (size_t x = 0; x < this->wall->width; ++x)
    {
        for (size_t y = 0; y < this->wall->height; ++y)
        {
            pos.x = x;
            pos.y = y;
            if (this->snake->overlap(pos)
                || this->wall->overlap(pos))
            {
                this->removeArcsToNode(x, y);
                this->graph->setIsOccupied(posToIndex(pos, this->wall->width), true);
            }   
            else
            {
                this->addArcsToNode(x, y);
                this->graph->setIsOccupied(posToIndex(pos, this->wall->width), false);
            }
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
    std::cout << "Collision!" << std::endl
        << "press Enter..." << std::endl;
    getchar();
    // Sleep(COLLIDE_TIME * 1000);
    this->debug.on = false;
    this->snake->reset(this->wall->width, this->wall->height);
    this->apple->place(this->wall, this->snake);    
}

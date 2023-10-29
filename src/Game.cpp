#include <conio.h>
#include <Windows.h>
#include <synchapi.h>
#include <limits>
#include <algorithm>
#include <random>
#include <vector>
#include <algorithm>
#include <thread>
#include "game.h"
#include "apple.h"
#include "define.h"

Game::Game(Wall *wall, Snake *snake, Graph *graph)
    : wall(wall),
    snake(snake),
    graph(graph),
    apple(new Apple),
    speed(1),
    growSpeed(GROW_SPEED),
    fps(FPS)
{
    this->snake->reset(this->wall->width, this->wall->height);
    this->apple->place(this->wall, this->snake);
    dijkstraSnake();
    // infiniteSnake();
    // userSnake();
}

void Game::dijkstraSnake()
{
    while (true)
    {
        std::vector<size_t> path;
        size_t start = posToIndex(this->snake->getHeadPos(), this->wall->width);
        size_t goal = posToIndex(this->apple->pos, this->wall->width);
        bool goalInReach = (this->graph->plusCourtChemin(start, goal, path)
            != std::numeric_limits<unsigned int>::max());
        if (!goalInReach)
        {
            // this->fps = 3;

            Position eventualExit = getEventualExit(start);
            std::cout << "eventualExit: " << eventualExit << std::endl;
            getchar();
            // move the furthest away from eventualExit

            this->tick(getDirToBiggestRoom(getAvailableDirs()));
            continue ;
        }
        else
            this->fps = FPS;
        Position next_pos = indexToPos(path[1], this->wall->width);
        enum Direction dir = this->getDir(this->snake->getHeadPos(), next_pos);
        this->tick(dir);
    }
}

Position Game::getEventualExit(size_t start)
{
    size_t a = 0;
    size_t b = 0;
    size_t bodySegment;

    for (size_t i = 0; i < this->snake->getLength(); ++i)
    {
        bodySegment = posToIndex(this->snake->getBlocPos(i), this->wall->width);
        if (!this->graph->reachable(start, bodySegment))
            break ;
        else
            a = i;
    }
    size_t lastSnakeBloc = posToIndex(this->snake->getBlocPos(this->snake->getLength() - 1), this->wall->width);
    if (this->graph->reachable(start, lastSnakeBloc))
    {
        for (size_t i = this->snake->getLength() - 1; i >= 0; --i)
        {
            bodySegment = posToIndex(this->snake->getBlocPos(i), this->wall->width);
            if (!this->graph->reachable(start, bodySegment))
            {
                b = i + 1;
                break;
            }
        }
    }
    else
    {
        for (size_t i = this->snake->getLength() - 1; i >= 0; --i)
        {
            bodySegment = posToIndex(this->snake->getBlocPos(i), this->wall->width);
            if (this->graph->reachable(start, bodySegment))
            {
                b = i;
                break ;
            }
        }
    }
    return indexToPos(std::max(a, b), this->wall->width);
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

std::vector<Direction> Game::getAvailableDirs()
{
    std::vector<Direction> res;
    Position snakeHead;
    Position neighbor;
    enum Direction dir;

    for (dir = LEFT; dir != NONE; ++dir)
    {
        snakeHead = this->snake->getHeadPos();
        neighbor = snakeHead.neighbor(dir, 1);
        // std::cout << "snakeHead: " << snakeHead << std::endl;
        // std::cout << "neighbor " << dir << ": " << neighbor << std::endl;            
        if (this->graph->hasArc(posToIndex(snakeHead, this->wall->width),
            posToIndex(neighbor, this->wall->width)))
        {
            res.push_back(dir);
        }
    }
    return res;
}

size_t Game::getDirRoomSize(Direction dir)
{
    size_t res;

    Snake temp = *(this->snake);
    this->snake->move(dir);
    this->updateGraph();
    res = this->graph->areaSize(posToIndex(this->snake->getHeadPos(), this->wall->width));
    *(this->snake) = temp;
    this->updateGraph();
    return res;
}

Direction Game::getDirToBiggestRoom(const std::vector<Direction> &dirs)
{
    std::vector<size_t> roomSizes(dirs.size());
    size_t currRoom;
    size_t maxRoom = 0;
    Direction maxRoomDir = NONE;

    for (size_t i = 0; i < dirs.size(); ++i)
    {
        currRoom = getDirRoomSize(dirs[i]);
        std::cout << dirs[i] << ":" << currRoom << std::endl;
        if (currRoom > maxRoom)
        {
            maxRoom = currRoom;
            maxRoomDir = dirs[i];
        }
    }
    return maxRoomDir;
}

bool Game::pathExists()
{
    std::vector<size_t> path;
    return (this->graph->plusCourtChemin(
        posToIndex(this->snake->getHeadPos(), this->wall->width),
        posToIndex(this->apple->pos, this->wall->width), path)
        != std::numeric_limits<unsigned int>::max());
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

void Game::display()
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
    Sleep(COLLIDE_TIME * 1000);
    this->snake->reset(this->wall->width, this->wall->height);
    this->apple->place(this->wall, this->snake);    
}

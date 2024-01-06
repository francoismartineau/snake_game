#include <windows.h>
#include <conio.h>
#include "game.h"
#include "util.h"

void Game::dijkstraSnake()
{

    this->draw();
    while (true)
    {
        if(_kbhit())
            this->keyInput();
        if (!this->dijkstraOn)
        {
            this->tick(this->survive(this->snake->dir));
            continue;
        }
        size_t start = posToIndex(this->snake->getHeadPos(), this->wall->width);
        size_t goal = posToIndex(this->apple->pos, this->wall->width);
		std::deque<size_t> path;
        bool pathExists = this->graph->shortestPath(start, goal, path) != std::numeric_limits<unsigned int>::max();
        if (pathExists)
        {
	        this->debug.on = false;
			usePath(path);
        }
        else
        {
			Direction dir = solveExitPoint(start);
			this->tick(dir);
        }
    }
}

void Game::usePath(const std::deque<size_t> &path)
{
	this->fps = FPS;
	Direction dir;

    std::cout << "curr_pos: " << this->snake->getHeadPos() << std::endl;
	// for (size_t i = 0; i < path.size(); ++i)
	for (size_t i = 0; i < 2; ++i)
	{
		Position next_pos = indexToPos(path[i], this->wall->width);
		dir = this->dirToPos(this->snake->getHeadPos(), next_pos);
		std::cout << "path index: " << i << std::endl
            << "path[i]: " << path[i] << std::endl
            << "available dirs: " << this->dirsAvailable(this->snake->getHeadPos()) << std::endl 
            << " dir: " << dir << std::endl
            << "next_pos: " << next_pos << std::endl;        
        waitForEnterKey();
		this->tick(dir);
	}
	// std::cout << "goal reached" << std::endl;
	// Sleep(300);
}

Direction Game::solveExitPoint(size_t start)
{
	this->fps = 3;
	Position exitPoint = getExitPoint(start);
	this->debug.on = true;
	this->debug.pos = exitPoint;
	std::cout << exitPoint << std::endl;
	std::vector<Direction> dirs = dirsAvailable(this->snake->getHeadPos());
	Direction dir = dirToBiggestRoom(dirs);
	if (dir == NONE)
	{
		dir = avoidPosition(this->snake->getHeadPos(), exitPoint);
	}
	if (dir == NONE && dirs.size())
	{
		dir = dirs[0];
	}
	return dir;
}

Position Game::getExitPoint(size_t start)
{
    size_t a = 0; // last reachable in a row from start
    for (size_t i = 0; i < this->snake->getLength(); ++i)
    {
        size_t bodySegment = posToIndex(this->snake->getBlocPos(i), this->wall->width);
        if (this->graph->reachable(start, bodySegment))
            a = i;
        else
            break ;
    }

    size_t b = 0; // last reachable
    for (size_t i = this->snake->getLength() - 1; i < this->snake->getLength(); --i)
    {
        size_t bodySegment = posToIndex(this->snake->getBlocPos(i), this->wall->width);
        if (this->graph->reachable(start, bodySegment))
        {
            b = i;
            break;
        }
    }
    return this->snake->getBlocPos(std::max(a, b));
}

Direction Game::avoidPosition(Position curr, Position avoid)
{
    std::vector<Direction> dirs;
    if (avoid.x <= curr.x)
        dirs.push_back(RIGHT);
    if (curr.x <= avoid.x)
        dirs.push_back(LEFT);
    if (avoid.y <= curr.y)
        dirs.push_back(DOWN);
    if (curr.y <= avoid.y)
        dirs.push_back(UP);
    for (auto dir: dirs)
    {
        size_t neighbor = posToIndex(curr.neighbor(dir, 1), this->wall->width);
        if (!this->graph->nodes[neighbor].occupied)
            return dir;
    }
    return NONE;
}

// -- directions --
std::vector<Direction> Game::dirsAvailable(Position pos)
{
    std::vector<Direction> res;
    Position neighbor;

    std::vector dirs = {LEFT, UP, RIGHT, DOWN};
    for (const Direction dir: dirs)
    {
        neighbor = pos.neighbor(dir, 1);
        if (this->graph->hasEdge(posToIndex(pos, this->wall->width),
            posToIndex(neighbor, this->wall->width)))
        {
            res.push_back(dir);
        }
    }
    return res;
}

Direction Game::dirToPos(Position from, Position to)
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

size_t Game::dirRoomSize(Direction dir)
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

Direction Game::dirToBiggestRoom(const std::vector<Direction> &dirs)
{
    if (dirs.size() == 0)
        return NONE;
    std::vector<size_t> roomSizes(dirs.size());
    Direction maxRoomDir = NONE;
    size_t currRoom = dirRoomSize(dirs[0]);
    size_t maxRoom = currRoom;

    for (size_t i = 1; i < dirs.size(); ++i)
    {
        currRoom = dirRoomSize(dirs[i]);
        if (currRoom > maxRoom)
        {
            maxRoom = currRoom;
            maxRoomDir = dirs[i];
        }
    }
    return maxRoomDir;
}

#include <iostream>
#include "define.h"


Position::Position()
{
    this->x = 0;
    this->y = 0;  
}


Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

Position::Position(const Position &pos)
{
    this->x = pos.x;
    this->y = pos.y;
}


bool Position::operator==(const Position & pos) const
{
    return (x == pos.x and y == pos.y);
}

std::ostream & operator<<(std::ostream & os, const Position & pos)
{
    os << "[" << pos.x << ", " << pos.y << "]";
    return os;
}

void Position::move(const Direction & dir, const int & speed)
{
    switch (dir)
    {
    case LEFT:
        this->x -= speed;
        break;
    case UP:
        this->y -= speed;
        break;
    case RIGHT:
        this->x += speed;
        break;
    case DOWN:
        this->y += speed;
        break;
    }
}

Direction reverse(Direction dir)
{
    switch (dir)
    {
    case UP:
        dir = DOWN;
        break;
    case DOWN:
        dir = UP;
        break;
    case LEFT:
        dir = RIGHT;
        break;
    case RIGHT:
        dir = LEFT;
        break;
    }
    return dir;
}


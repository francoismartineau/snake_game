#include <iostream>
#include "define.h"

size_t Position::w = 0;
size_t Position::h = 0;

Position::Position()
{
    this->x = 0;
    this->y = 0;  
}


Position::Position(size_t x, size_t y)
{
    this->x = x;
    this->y = y;
}

Position::Position(const Position &pos)
{
    this->x = pos.x;
    this->y = pos.y;
}


bool Position::operator==(Position pos) const
{
    return (this->x == pos.x && this->y == pos.y);
}

std::ostream & operator<<(std::ostream & os, const Position & pos)
{
    os << "[" << pos.x << ", " << pos.y << "]";
    return os;
}

void Position::move(const Direction & dir, size_t speed)
{
    switch (dir)
    {
    case LEFT:
        if (speed <= this->x)
            this->x -= speed;
        else
            this->x = this->w - (speed - this->x);
        break;
    case UP:
        if (speed <= this->y)
            this->y -= speed;
        else
            this->y = this->h - (speed - this->y);        
        break; 
    case RIGHT:
        this->x += speed;
        this->x %= this->w;
        break;
    case DOWN:
        this->y += speed;
        this->y %= this->h;
        break;
    default:
        break;
    }

}

std::ostream & operator<<(std::ostream & os, Direction dir)
{
    switch (dir)
    {
    case LEFT:
        os << "LEFT";
        break;
    case UP:
        os << "UP";
        break;
    case RIGHT:
        os << "RIGHT";
        break;
    case DOWN:
        os << "DOWN";
        break;
    default:
        os << "NONE";
        break;
    }
    return os;
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
    default:
        break;
    }
    return dir;
}


Position indexToPos(size_t i, size_t width)
{
    return Position(i % width, i / width);
}

size_t coordToIndex(size_t x, size_t y, size_t width)
{
    return x + y * width;
}

size_t posToIndex(Position pos, size_t width)
{
    return coordToIndex(pos.x, pos.y, width);
}


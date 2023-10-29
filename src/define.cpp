#include <iostream>
#include <vector>
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

std::ostream &operator<<(std::ostream &os, const std::vector<Direction> &dirs)
{
    for (const Direction& dir : dirs) {
        os << dir << " ";
    }
    return os;
}


std::ostream &operator<<(std::ostream & os, const Position & pos)
{
    os << "[" << pos.x << ", " << pos.y << "]";
    return os;
}

Position Position::move(const Direction & dir, size_t speed)
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
    return *this;
}

Position Position::neighbor(const Direction & dir, size_t speed)
{
    Position res = *this;

    switch (dir)
    {
    case LEFT:
        if (speed <= res.x)
            res.x -= speed;
        else
            res.x = res.w - (speed - res.x);
        break;
    case UP:
        if (speed <= res.y)
            res.y -= speed;
        else
            res.y = res.h - (speed - res.y);        
        break; 
    case RIGHT:
        res.x += speed;
        res.x %= res.w;
        break;
    case DOWN:
        res.y += speed;
        res.y %= res.h;
        break;
    default:
        break;
    }
    return res;   
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

Direction& operator++(Direction& d)
{
    switch(d)
    {
        case Direction::LEFT:
            return d = Direction::UP;
        case Direction::UP:
            return d = Direction::RIGHT;
        case Direction::RIGHT:
            return d = Direction::DOWN;
        case Direction::DOWN:
            return d = Direction::NONE;
        case Direction::NONE:
        default:
            return d = Direction::LEFT;
    }
}

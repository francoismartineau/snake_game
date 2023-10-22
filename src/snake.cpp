#include <Windows.h>
#include "snake.h"
#include "define.h"


Snake::Snake(size_t x, size_t y, size_t length, const Direction & dir)
    : oriX(x),
    oriY(y),
    oriLength(length),
    oriDir(dir),
    dir(dir),
    speed(1)
{
}

const Position & Snake::getHeadPos() const
{
    return this->getBlocPos(0);
}

void Snake::reset(size_t w, size_t h)
{
    Position pos(this->oriX, this->oriY);
    this->dir = this->oriDir;
    this->length = this->oriLength;
    this->blocs.clear();
    this->blocs.push_back(pos);
    for(size_t i = 1; i < this->length; ++i)
    {
        pos.move(reverse(this->dir), 1);
        this->blocs.push_back(pos);
    }
}

bool Snake::overlap(Position pos) const
{
    for(size_t i = 0; i < this->length; i++)
        if (pos == this->getBlocPos(i))
            return true;
    return false;
}


const Position & Snake::getBlocPos(size_t index) const
{
    return  this->blocs[index];
}

size_t Snake::getLength() const
{
    return this->length;
}

void Snake::grow(size_t growSize)
{
    for(size_t i = 0; i < growSize; ++i)
        this->blocs.push_back(this->blocs.back());
    this->length += growSize;
}

void Snake::move(Direction dir)
{
    if (dir != NONE && dir != reverse(this->dir))
        this->dir = dir;
    for(size_t i = this->length - 1 ; i > 0; i--)
        this->blocs[i] = this->blocs[i - 1];
    this->blocs[0].move(this->dir, this->speed);
}

std::ostream & operator<<(std::ostream & os, const Snake & s)
{
    for(size_t i = 0; i < s.getLength(); i++)
        os << "POS " << i << ": [" << s.blocs[i].x << "," << s.blocs[i].y <<"]\n";
    os << '\n';
    std::cout << s.blocs[s.getLength() - 1] << '\n';
    return os;
}


#include "snake.h"
#include "define.h"


Snake::Snake(const int & x, const int & y, int length, const Direction & dir)
    : oriX(x), oriY(y), oriLength(length), oriDir(dir), dir(dir), speed(1)
{
    reset();
}

const Position & Snake::getHeadPos() const
{
    return this->getBlocPos(0);
}


void Snake::reset()
{
    Position pos(this->oriX, this->oriY);
    this->dir = this->oriDir;
    this->length = this->oriLength;
    this->blocs.clear();
    this->blocs.push_back(pos);
    for(unsigned int i = 1; i < this->length; ++i)
    {
        pos.move(reverse(this->dir), 1);
        this->blocs.push_back(pos);
    }
}

bool Snake::overlap(Position pos)
{
    for(unsigned int i = 0; i < this->length; i++)
        if (pos == this->getBlocPos(i))
            return true;
    return false;
}


const Position & Snake::getBlocPos(const int & index) const
{
    return  this->blocs[index];
}

const unsigned int & Snake::getLength() const
{
    return this->length;
}

void Snake::grow(const int & growSize)
{
    for(int i = 0; i < growSize; ++i)
        this->blocs.push_back(this->blocs.back());
    this->length += growSize;
}

void Snake::move()
{
    for(unsigned int i = this->length - 1 ; i > 0; i--)
        this->blocs[i] = this->blocs[i - 1];
    this->blocs[0].move(this->dir, this->speed);
}

void Snake::move(const Direction & dir)
{
    if (dir != NONE)
        this->dir = dir;
    this->move();
}

std::ostream & operator<<(std::ostream & os, const Snake & s)
{
    for(unsigned int i = 0; i < s.getLength(); i++)
        os << "POS " << i << ": [" << s.blocs[i].x << "," << s.blocs[i].y <<"]\n";
    os << '\n';
    std::cout << s.blocs[s.getLength() - 1] << '\n';
    return os;
}


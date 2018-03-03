/*
 * \file Snake.cpp
 * \date Oct 28, 2017
 * \author François Martineau
 */
#include "Snake.h"



Snake::Snake(const int & oriX, const int & oriY, const unsigned int & length): m_oriX(oriX), m_oriY(oriY), m_oriLenght(length)
{
    reset();
}

void Snake::reset()
{
    Position pos;
    pos.x = m_oriX;
    pos.y = m_oriY;
    m_length = m_oriLenght;
    snakePos.clear();
    snakePos.push_back(pos);
    for(unsigned int i = 1; i <= m_length; i++){
        pos.y ++;
        snakePos.push_back(pos);
    }
}

const Position & Snake::getPiecePos(const int & index) const
{
    //Position test = snakePos[index];
    //int xx = test.x;
    //int yy = test.y;

    return  snakePos[index];
}

const unsigned int & Snake::getLenght() const
{
    return m_length;
}

void Snake::grow(const int & growSize)
{
    for(int i = 0; i < growSize; i++){
        snakePos.push_back(snakePos.back());
    }
    m_length += growSize;
}

void Snake::move(const Direction & dir, const int & speed)
{
    for(int i = m_length - 1 ; i > 0; i--){
        snakePos[i] = snakePos[i - 1];
    }
    switch (dir) {
    case LEFT:
        snakePos[0].x -= speed;
        break;
    case UP:
        snakePos[0].y -= speed;
        break;
    case RIGHT:
        snakePos[0].x += speed;
        break;
    case DOWN:
        snakePos[0].y += speed;
        break;
    }
}

std::ostream & operator<<(std::ostream & os,const Snake & sn){
    for(unsigned int i = 0; i < sn.m_length; i++){
        os << "POS " << i << ": [" << sn.snakePos[i].x << "," << sn.snakePos[i].y <<"]\n";
    }
    os << '\n';
    std::cout << sn.snakePos[sn.getLenght() - 1] << '\n';

    return os;

}


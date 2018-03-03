/*
 * \file Snake.h
 * \date Oct 27, 2017
 * \author François Martineau
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <iostream>     //ostream
#include <vector>
#include "Utility.h"



class Snake {
public:
    Snake(const int & oriX, const int & oriY, const unsigned int & length);
    void reset();
    const Position & getPiecePos(const int & index) const;
    const unsigned int & getLenght() const;
    void grow(const int & size);
    void move(const Direction & dir, const int & speed);
    friend std::ostream & operator<<(std::ostream & os,const Snake & sn);

private:
    int m_oriX;
    int m_oriY;
    int m_oriLenght;
    std::vector <Position> snakePos;
    unsigned int m_length;
};



#endif /* SNAKE_H_ */

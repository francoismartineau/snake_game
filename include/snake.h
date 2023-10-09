#ifndef SNAKE_H_
#define SNAKE_H_

#include <iostream>     //ostream
#include <vector>
#include "define.h"



class Snake {
public:
    Snake(const int & x, const int & y, int length, const Direction & dir);
    void reset();
    bool overlap(Position pos);
    const Position & getBlocPos(const int & index) const;
    const Position & getHeadPos() const;
    const unsigned int & getLength() const;
    void grow(const int & size);
    void move();
    void move(const Direction & dir);
    void setDir(const Direction & dir);
    friend std::ostream & operator<<(std::ostream & os, const Snake & sn);
    Direction dir;
    int speed;

private:
    int oriX;
    int oriY;
    int oriLength;
    Direction oriDir;
    std::vector <Position> blocs;
    unsigned int length;
};



#endif /* SNAKE_H_ */

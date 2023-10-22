#ifndef SNAKE_H_
#define SNAKE_H_

#include <iostream>     //ostream
#include <vector>
#include "define.h"



class Snake {
public:
    Snake(size_t x, size_t y, size_t length, const Direction & dir);
    void reset(size_t w, size_t h);
    bool overlap(Position pos) const; 
    const Position & getBlocPos(size_t index) const;
    const Position & getHeadPos() const;
    size_t getLength() const;
    void grow(size_t size);
    void move();
    void move(Direction dir);
    void setDir(const Direction & dir);
    friend std::ostream & operator<<(std::ostream & os, const Snake & sn);

private:
    size_t oriX;
    size_t oriY;
    size_t oriLength;
    Direction oriDir;
public:
    Direction dir;
    int speed;
private:
    std::vector <Position> blocs;
    size_t length;
};



#endif /* SNAKE_H_ */

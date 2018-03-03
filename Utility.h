/*
 * \file Utility.h
 * \date Oct 27, 2017
 * \author François Martineau
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>

struct Position {
    int x;
    int y;
    bool operator==(const Position & pos) const;
    friend std::ostream & operator<<(std::ostream & os, const Position & pos);
};


enum Direction {
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3
};

enum Texture {
    SNAKE = '|',
    WALL = '#',
    APPLE = 'O',
    EMPTY = ' '
};

#endif /* UTILITY_H_ */

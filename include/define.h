#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>

enum Direction {
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    NONE = 4
};

Direction reverse(Direction dir);

struct Position
{
    Position();
    Position(int x, int y);
    Position(const Position &pos);
    int x;
    int y;
    bool operator==(const Position & pos) const;
    friend std::ostream & operator<<(std::ostream & os, const Position & pos);
    void move(const Direction & dir, const int & speed);
};

enum Texture {
    SNAKE = '|',
    SNAKE_HEAD = '-',
    WALL = '#',
    APPLE = 'O',
    EMPTY = ' '
};

#endif /* UTILITY_H_ */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <vector>

enum Direction {
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    NONE = 4
};

Direction& operator++(Direction& d);

std::ostream &operator<<(std::ostream &os, Direction dir);
std::ostream &operator<<(std::ostream &os, const std::vector<Direction> &dirs);


Direction reverse(Direction dir);

struct Position
{
    Position();
    Position(size_t x, size_t y);
    Position(const Position &pos);
    size_t x;
    size_t y;
    static size_t w;
    static size_t h;
    bool operator==(Position pos) const;
    friend std::ostream & operator<<(std::ostream & os, const Position & pos);
    Position move(const Direction & dir, size_t speed);
    Position neighbor(const Direction & dir, size_t speed);
    void teleport();
};

enum Texture {
    SNAKE = '|',
    SNAKE_HEAD = '-',
    WALL = '#',
    APPLE = 'O',
    EMPTY = ' '
};

size_t coordToIndex(size_t x, size_t y, size_t width);
size_t posToIndex(Position pos, size_t width);
Position indexToPos(size_t i, size_t width);

#endif /* UTILITY_H_ */

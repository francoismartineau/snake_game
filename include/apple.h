#ifndef APPLE_H_
#define APPLE_H_
#include "define.h"
#include "snake.h"
#include "wall.h"

class Apple
{
public:
    Apple();
    void place(Wall *wall, Snake *snake);
    void setPosition(const Position & pos);
    const Position & getPosition() const;
    Position pos;
    bool hidden;
};

#endif /* APPLE_H_ */

#ifndef APPLE_H_
#define APPLE_H_
#include "define.h"
#include "snake.h"

class Apple
{
public:
    Apple();
    void place(int width, int height, Snake *snake);
    void setPosition(const Position & pos);
    const Position & getPosition() const;
    Position pos;

};



#endif /* APPLE_H_ */

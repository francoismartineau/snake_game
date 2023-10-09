#include "apple.h"

Apple::Apple()
{
}


void Apple::place(int width, int height, Snake *snake)
{
    do
    {
        this->pos.x = (rand() % (width - 2)) + 1;
        this->pos.y = (rand() % (height - 2)) + 1;
    }
    while (snake->overlap(this->pos));
}


void Apple::setPosition(const Position & pos)
{
    this->pos = pos;
}
const Position & Apple::getPosition() const
{
    return this->pos;
}

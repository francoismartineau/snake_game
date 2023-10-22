#include "apple.h"

Apple::Apple()
    : hidden(false)
{
}

void Apple::place(Wall *wall, Snake *snake)
{
    if (snake->getLength() + wall->getLength()
        >= wall->width*wall->height)
    {
        this->hidden = true;
        return;
    }
    do
    {
        this->pos.x = (rand() % wall->width);
        this->pos.y = (rand() % wall->height);
    }
    while (snake->overlap(this->pos)
        || wall->overlap(this->pos));
    this->hidden = false;
}


void Apple::setPosition(const Position & pos)
{
    this->pos = pos;
}
const Position & Apple::getPosition() const
{
    return this->pos;
}

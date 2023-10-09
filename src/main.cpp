#include <iostream>
#include "Game.h"

int main()
{
    int width = 18;
    int height = 6;

    Game game(
        new Wall(width, height),
        new Snake(2, height-3, 2, UP)
    );
    return 0;
}

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include "snake.h"
#include "wall.h"
#include "apple.h"


class Game
{
public:
    Game(Wall *wall, Snake *snake);
    ~Game();
    Wall * wall;
    Snake  * snake;
    Apple * apple;

private:
    void tick();
    void tick(Direction dir);
    bool collision();
    void collide();
    Direction keyInput();
    void draw() const;
    bool drawSnake(const int & x, const int & y) const;
    bool drawWall(const int & x, const int & y) const;
    bool drawApple(const int & x, const int & y) const;
    void drawPixel(Texture texture) const;


    int speed;
    int growSpeed;
    Direction m_direction;
};



#endif /* GAME_H_ */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <chrono>
#include "snake.h"
#include "wall.h"
#include "apple.h"
#include "graph.h"
#include "define.h"

class Game
{
public:
    Game(Wall *wall, Snake *snake, Graph *graph);
    Wall *wall;
    Snake  *snake;
    Graph *graph;
    Apple *apple;
    ~Game();

private:
    void tick();
    void tick(Direction dir);
    bool collision();
    void collide();
    Direction keyInput();
    void draw() const;
    bool drawSnake(size_t x, size_t y) const;
    bool drawWall(size_t x, size_t y) const;
    bool drawApple(size_t x, size_t y) const;
    void drawPixel(Texture texture) const;
    void updateGraph();
    void addArcsToNode(size_t x, size_t y);
    void removeArcsToNode(size_t x, size_t y);
    Direction survive(Position headPos);
    Direction getDir(Position from, Position to);
    void dijkstraSnake();
    void userSnake();
    void infiniteSnake();
    void takeFrameTime();
    void fpsSync();

    int speed;
    int growSpeed;
    Direction m_direction;
    std::chrono::time_point<std::chrono::high_resolution_clock> frameTime;
};

Direction getDir(Position from, Position to);

#endif /* GAME_H_ */

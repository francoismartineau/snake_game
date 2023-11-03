#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <deque>
#include "snake.h"
#include "wall.h"
#include "apple.h"
#include "graph.h"
#include "define.h"

#define FPS 30.0
#define GROW_SPEED 2
#define COLLIDE_TIME 5
#define WALLCHAR '#'

class Game
{
public:
    Game(Wall *wall, Snake *snake, Graph *graph);
    ~Game();
    Wall *wall;
    Snake  *snake;
    Graph *graph;
    Apple *apple;

private:
    void gameChoice();
    void tick();
    void tick(Direction dir);
    bool collision();
    void collide();
    
    // --  Display / IO --
    void draw() const;
    bool drawSnake(size_t x, size_t y) const;
    bool drawWall(size_t x, size_t y) const;
    bool drawApple(size_t x, size_t y) const;
    void drawPixel(Texture texture) const;
    bool drawDebug(size_t x, size_t y) const;
    struct Debug
    {
        bool on;
        Position pos;
    };
    Debug debug;
    void freezeFrame();
    void takeFrameTime();
    void fpsSync() const;
    std::chrono::time_point<std::chrono::high_resolution_clock> frameTime;
    unsigned int fps;
    Direction keyInput();

    // -- graph --
    void updateGraph();
    void addArcsToNode(size_t x, size_t y);
    void removeArcsToNode(size_t x, size_t y);

    // -- dijkstra --
    void dijkstraSnake();
    void usePath(const std::deque<size_t> &path);
    Direction solveExitPoint(size_t start);
    Position getExitPoint(size_t start);
    Direction avoidPosition(Position curr, Position avoid);
    std::vector<Direction> dirsAvailable(void);
    size_t dirRoomSize(Direction dir);
    Direction dirToBiggestRoom(const std::vector<Direction> &dirs);
    Direction dirToPos(Position from, Position to);

    // ----
    void userSnake(bool survive);
    void infiniteSnake();
    Direction survive(Direction dir);

    // ----
    int speed;
    int growSpeed;
    Direction m_direction;
};

#endif /* GAME_H_ */

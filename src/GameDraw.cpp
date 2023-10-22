#include <sstream>
#include <thread>
#include "Game.h"

void Game::draw() const{
    system("cls");
    for (size_t y = 0; y < this->wall->height; y++)
    {
        for (size_t x = 0; x < this->wall->width; x++)
        {
            if(!drawWall(x, y)
                && !drawApple(x, y)
                && !drawSnake(x, y))
                drawPixel(EMPTY);
        }
        std::cout << '\n';
    }
    // std::cout << "CONTROLS: I J K L\n";
}

bool Game::drawSnake(size_t x, size_t y) const
{
    if (this->snake->overlap(Position(x, y)))
    {
        if (this->snake->getHeadPos() == Position(x, y))
            drawPixel(SNAKE_HEAD);
        else
            drawPixel(SNAKE);
        return true;
    }
    return false;
}

bool Game::drawWall(size_t x, size_t y) const
{
    if (this->wall->overlap(Position(x, y)))
    {
        drawPixel(WALL);
        return true;
    }
    return false;
}

bool Game::drawApple(size_t x, size_t y) const
{
    if (Position(x, y) == this->apple->getPosition()
        && !this->apple->hidden)
    {
        drawPixel(APPLE);
        return true;
    }
    return false;
}

void Game::drawPixel(Texture texture) const
{
    std::cout << (char)texture;
}

void Game::takeFrameTime()
{
    this->frameTime = std::chrono::high_resolution_clock::now();
}

void Game::fpsSync()
{
    auto endTime = std::chrono::high_resolution_clock::now();    // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - this->frameTime);
    int sleepTimeMs = std::max(
        0, 
        int(1.0 / FPS * 1000) - static_cast<int>(duration.count())
    );
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
}

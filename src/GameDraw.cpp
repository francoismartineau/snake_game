#include <sstream>
#include <iomanip>
#include <thread>
#include "game.h"
#include "util.h"

void Game::draw() const{
    // system("cls");

    // if (draw to file):
    // if (this->drawToFile)
    //      create this->logFile, increment file name number
        // this->drawFile = createFile("log", ".txt");


    // drawPixel: if (draw to file): draw to file 
    // ...
    // if (draw to file): 
    //      close file
    std::cout << " ";
    for (size_t x = 0; x < this->wall->width; x++)
    {
        std::cout << x % 10;
    }
    std::cout << "\n";
    for (size_t y = 0; y < this->wall->height; y++)
    {

        std::cout << y % 10;
        for (size_t x = 0; x < this->wall->width; x++)
        {
            if(!drawDebug(x, y)
                && !drawWall(x, y)
                && !drawApple(x, y)
                && !drawSnake(x, y))
                drawPixel(EMPTY);
        }
        std::cout << '\n';
    }
}

bool Game::drawDebug(size_t x, size_t y) const
{
    if (!this->debug.on) // || x != this->debug.pos.x || y != this->debug.pos.y)
        return false;
    if (!(Position(x, y) == debug.pos))
        return false;
    drawPixel(DEBUG);
    return true;
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

void Game::fpsSync() const
{
    auto endTime = std::chrono::high_resolution_clock::now();    // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - this->frameTime);
    int sleepTimeMs = std::max(
        0, 
        int(1.0 / this->fps * 1000) - static_cast<int>(duration.count())
    );
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
}

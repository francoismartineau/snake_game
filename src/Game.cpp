#include <conio.h>
#include <Windows.h>
#include <synchapi.h>
#include "Game.h"
#include "apple.h"
#include "define.h"

Game::Game(Wall *wall, Snake *snake)
    : snake(snake),
    wall(wall),
    apple(new Apple),
    speed(1),
    growSpeed(4)
{
    this->apple->place(this->wall->width, this->wall->height, this->snake);
    int yTop = 2;
    int yBottom = this->wall->height-2;
    int xRight = this->wall->width-1;
    int xLeft = 2;
    int y = this->wall->height-3;
    int x = xLeft;

    while(true)
    {
        while (true)
        {
            if (this->snake->getHeadPos().y != yTop)
            {
                do
                {
                    this->tick(UP);
                    std::cout << "up" << std::endl;
                }
                while (this->snake->getHeadPos().y > yTop);    
            }
            else
            {
                do
                {
                    this->tick(DOWN);
                    std::cout << "down" << std::endl;
                }
                while (this->snake->getHeadPos().y < yBottom);
            }
            if (this->snake->getHeadPos().x < xRight - 1)
            {
                this->tick(RIGHT);
                std::cout << "right" << std::endl;
            }
            else
                break;
        }
        this->tick(UP);
        do
        {
            this->tick(LEFT);
        }
        while (this->snake->getHeadPos().x >= xLeft);
        do
        {
            this->tick(DOWN);
            ++y;
        }
        while (this->snake->getHeadPos().y < yBottom);
        this->tick(RIGHT);
    }
}

void Game::tick(Direction dir)
{
    this->snake->move(dir);    
    if (collision())
    {
        this->snake->reset();
        this->apple->place(this->wall->width, this->wall->height, this->snake);
    }
    else if (this->apple->pos == this->snake->getBlocPos(0))
    {
        this->snake->grow(this->growSpeed);
        this->apple->place(this->wall->width, this->wall->height, this->snake);
    }
    this->draw();
    Sleep(100);
}

void Game::tick()
{
    if(_kbhit())
        this->snake->move(keyInput());
    else
        this->snake->move();    
    if (this->collision())
    {
        this->snake->reset();
        this->apple->place(this->wall->width, this->wall->height, this->snake);
    }
    else if (this->apple->pos == this->snake->getBlocPos(0))
    {
        this->snake->grow(this->growSpeed);
        this->apple->place(this->wall->width, this->wall->height, this->snake);
    }
    this->draw();
}

Game::~Game()
{
  delete this->apple;
  delete this->wall;
  delete this->snake;
}

Direction Game::keyInput()
{
    char current = _getch();
    switch (current)
    {
    case 'i':
        return UP;
    case 'j':
        return LEFT;
    case 'k':
        return DOWN;
    case 'l':
        return RIGHT;
    }
    return NONE;
}

bool Game::collision()
{
    for (int i = 0; i < this->wall->getBlocQty(); ++i)
    {
        if(snake->getHeadPos() == this->wall->getBlocPos(i))
        {
            collide();
            return true;
        }
    }
    for(unsigned int i = 1; i < this->snake->getLength(); ++i)
    {
        if(snake->getHeadPos() == snake->getBlocPos(i))
        {
            collide();
            return true;
        }
    }
    return false;
}

void Game::collide()
{
    std::cout << "Collision!" << std::endl;
    Sleep(1000);
    snake->reset();
}

#include <sstream>
#include "Game.h"

void Game::draw() const{
    system("cls");
    for(int y = 0; y < this->wall->height; y++ ){
        for(int x = 0; x < this->wall->width; x++){
            if(!drawWall(x, y)
                && !drawApple(x, y)
                && !drawSnake(x, y))
                drawPixel(EMPTY);
        }
        std::cout << '\n';
    }
    std::cout << "CONTROLS: I J K L\n";
}

bool Game::drawSnake(const int & x, const int & y) const{
    if(this->snake->overlap(Position(x, y)))
    {
        if (this->snake->getHeadPos() == Position(x, y))
            drawPixel(SNAKE_HEAD);
        else
            drawPixel(SNAKE);
        return true;
    }
    return false;
}

bool Game::drawWall(const int & x, const int & y) const{
    bool drewWall = false;
    const int * wallPieceNb = & wall->getBlocQty();
    for(int i = 0; i < * wallPieceNb; i++){
        const Position * wallPiecePos = & wall->getBlocPos(i);
        if(x == wallPiecePos->x and y == wallPiecePos->y){
            drawPixel(WALL);
            drewWall = true;
        }
    }
    return drewWall;
}

bool Game::drawApple(const int & x, const int & y) const
{
    bool drewApple = false;

    if(x == this->apple->getPosition().x and y == this->apple->getPosition().y)
    {
        drawPixel(APPLE);
        drewApple = true;
    }
    return drewApple;

}

void Game::drawPixel(Texture texture) const{
    std::cout << (char)texture;

}

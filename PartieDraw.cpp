/*
 * \file PartieDraw.cpp
 * \date Oct 27, 2017
 * \author François Martineau
 */
#include "Partie.h"
#include <sstream>

void Partie::draw() const{
    system("cls");
    for(int y = 0; y < m_height; y++ ){
        for(int x = 0; x < m_width; x++){
            if(!drawSnake(x, y)){
                if(!drawWall(x, y)){
                    if(!drawApple(x, y)){
                        drawPixel(EMPTY);
                    }
                }
            }
        }
        std::cout << '\n';
    }
    std::cout << "SNAKE!\n";
}

bool Partie::drawSnake(const int & x, const int & y) const{
    bool drewSnake = false;
    const unsigned int * snakeLenght = & m_snake->getLenght();
    for(unsigned int i = 0; i < (*snakeLenght) - 1; i++){
        const Position * snakePiecePos = & m_snake->getPiecePos(i);
        if(x == snakePiecePos->x and y == snakePiecePos->y){
            drawPixel(SNAKE);
            drewSnake = true;
            break;
        }
    }
    return drewSnake;
}

bool Partie::drawWall(const int & x, const int & y) const{
    bool drewWall = false;
    const int * wallPieceNb = & m_wall->getWallPieceNb();
    for(int i = 0; i < * wallPieceNb; i++){
        const Position * wallPiecePos = & m_wall->getPiecePos(i);
        if(x == wallPiecePos->x and y == wallPiecePos->y){
            drawPixel(WALL);
            drewWall = true;
        }
    }
    return drewWall;
}

bool Partie::drawApple(const int & x, const int & y) const {
    bool drewApple = false;
    const Position * applePos = & m_apple->getPosition();
    if(x == applePos->x and y == applePos->y){
        drawPixel(APPLE);
        drewApple = true;
    }
    return drewApple;

}

void Partie::drawPixel(Texture texture) const{
    std::cout << (char)texture;

}

/*
 * \file Partie.cpp
 * \date Oct 27, 2017
 * \author Francois Martineau
 */
#include "Partie.h"
#include "Utility.h"
#include <conio.h>
#include "Windows.h"

Partie::Partie(const int & width, const int & height) :m_width(width), m_height(height){
    m_snake = new Snake(width/2, height/2, 10);
    m_wall = new Wall(m_width, m_height);
    m_apple = new Apple();
    placeApple();


    m_speed = 1; //une vitesse superieure a 1 n'est pas encore bien support�e
    m_growSpeed = 1;
    m_direction = (Direction)(rand() % 4);

    while(true){
        keyInput();
        m_snake->move(m_direction, m_speed);
        if(!collision())
            mangePomme();
        draw();
    }
}

Partie::~Partie(){
  delete m_apple;
  delete m_wall;
  delete m_snake;
}

void Partie::keyInput(){
    char p_up = 'i';
    char p_left = 'j';
    char p_down = 'k';
    char p_right = 'l';

    if(_kbhit()){
        char current = _getch();
        if(current == p_up)
            m_direction = UP;
        if(current == p_left)
            m_direction = LEFT;
        if(current == p_right)
            m_direction = RIGHT;
        if(current == p_down)
            m_direction = DOWN;
    }
}

bool Partie::collision(){
    const Position * headPos = & m_snake->getPiecePos(0);
    const int * wallPieceNb = & m_wall->getWallPieceNb();
    for(int i = 0; i < * wallPieceNb; i++){
        const Position * wallPiecePos =  & m_wall->getPiecePos(i);
        if(*headPos == *wallPiecePos){
            m_snake->reset();
            return true;
        }
    }
    const unsigned int * snakeLenght = & m_snake->getLenght();
    for(unsigned int i = 1; i < * snakeLenght; i++){
        const Position * snakePiecePos = & m_snake->getPiecePos(i);
        if(*headPos == *snakePiecePos){
            m_snake->reset();
            return true;
        }
    }
    return false;
}

void Partie::mangePomme(){
    const Position * headPos = & m_snake->getPiecePos(0);
    const Position * applePos = & m_apple->getPosition();
    if(*headPos == *applePos){
        m_snake->grow(m_growSpeed);
        placeApple();
    }
}

void Partie::placeApple(){
    Position applePos;
    bool validPos = false;
    const unsigned int * snakeLenght = & m_snake->getLenght();
    while(!validPos){
        applePos.x = (rand() % (m_width - 2)) + 1;
        applePos.y = (rand() % (m_height - 2)) + 1;

        for(unsigned int i = 0; i < * snakeLenght; i++){
            const Position * snakePiecePos = & m_snake->getPiecePos(i);
            if(!(applePos == *snakePiecePos)){
                validPos = true;
                break;
            }
        }
    }
    m_apple->setPosition(applePos);
}





/*
 * \file Partie.h
 * \date Oct 27, 2017
 * \author Francois Martineau
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include <iostream>
#include <string>
#include "Snake.h"
#include "Wall.h"
#include "Apple.h"


class Partie{
public:
    Partie(const int & width = 70, const int & height = 50);
    ~Partie();
private:
    bool collision();
    void mangePomme();
    void keyInput();
    void placeApple();
    void draw() const;
    bool drawSnake(const int & x, const int & y) const;
    bool drawWall(const int & x, const int & y) const;
    bool drawApple(const int & x, const int & y) const;
    void drawPixel(Texture texture) const;

    Wall * m_wall;
    Snake  * m_snake;
    Apple * m_apple;
    int m_speed;
    int m_growSpeed;
    unsigned short m_width;
    unsigned short m_height;
    Direction m_direction;
};



#endif /* PARTIE_H_ */

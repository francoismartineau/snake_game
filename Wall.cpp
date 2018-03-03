/*
 * \file Wall.cpp
 * \date Oct 28, 2017
 * \author François Martineau
 */
#include "Wall.h"




Wall::Wall(const int & width, const int & height){
    wallPieceNb = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(y == 0 or y == height-1){
                registerWallPosition(x, y);
            }
            else if(x == 0 or x == width - 1){
                registerWallPosition(x, y);
            }
        }
    }
}

const Position & Wall::getPiecePos(const int & index) const {
    return wallPos[index];
}

const int & Wall::getWallPieceNb() const {
    return wallPieceNb;
}

void Wall::registerWallPosition(const int & x, const int & y){
    wallPieceNb++;
    Position pos;
    pos.x = x;
    pos.y = y;
    wallPos.push_back(pos);
}

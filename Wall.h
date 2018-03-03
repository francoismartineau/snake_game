/*
 * \file Wall.h
 * \date Oct 27, 2017
 * \author François Martineau
 */

#ifndef WALL_H_
#define WALL_H_

#include <vector>
#include "Utility.h"

class Wall{
public:

    Wall(const int & width, const int & height);
    const Position & getPiecePos(const int & index) const;
    const int & getWallPieceNb() const;

private:
    void registerWallPosition(const int & x, const int & y);
    std::vector <Position> wallPos;
    int wallPieceNb;
};



#endif /* WALL_H_ */

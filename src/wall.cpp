#include "wall.h"

Wall::Wall(const int & width, const int & height)
    : width(width), height(height)
{
    this->blocQty = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(y == 0 or y == height-1){
                addBloc(x, y);
            }
            else if(x == 0 or x == width - 1){
                addBloc(x, y);
            }
        }
    }
}

const Position& Wall::getBlocPos(const int & index) const
{
    return this->blocs[index];
}

const int& Wall::getBlocQty() const
{
    return this->blocQty;
}

void Wall::addBloc(const int & x, const int & y)
{
    this->blocQty++;
    Position pos(x, y);
    this->blocs.push_back(pos);
}

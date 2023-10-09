#ifndef WALL_H_
#define WALL_H_

#include <vector>
#include "define.h"

class Wall
{
public:
    Wall(const int & width, const int & height);
    const Position & getBlocPos(const int & index) const;
    const int & getBlocQty() const;
    int width;
    int height;

private:
    void addBloc(const int & x, const int & y);
    std::vector <Position> blocs;
    int blocQty;
};



#endif /* WALL_H_ */

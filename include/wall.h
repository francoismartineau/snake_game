#ifndef WALL_H_
#define WALL_H_

#include <vector>
#include <string>
#include "define.h"

class Wall
{
public:
    Wall(std::string path);
    Wall(size_t width, size_t height);
    const Position & getBlocPos(size_t index) const;
    size_t getBlocQty() const;
    bool overlap(Position pos) const;
    size_t width;
    size_t height;
    size_t getLength() const;

private:
    void getSize(std::string txt);
    void addBloc(Position pos);
    void addBloc(size_t x, size_t y);
    std::vector <Position> blocs;
    size_t blocQty;
};



#endif /* WALL_H_ */

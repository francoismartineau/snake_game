#include <fstream>
#include <sstream>
#include "wall.h"


Wall::Wall(std::string path)
{
    std::ifstream file(path);

    if (file.is_open())
    {
        std::string txt((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        this->getSize(txt);
        size_t offs = 0;
        for (size_t i = 0; i < txt.length(); ++i)
        {
            if (txt[i] == WALLCHAR)
                this->addBloc(indexToPos(i-offs, this->width));
            if (txt[i] == '\n')
                ++offs;
        }                  
    }    
}

void Wall::getSize(std::string txt)
{
    this->width = 0;
    this->height = 0;
    std::istringstream iss(txt);
    std::string line;
    while (std::getline(iss, line))
    {
        ++this->height;
        if (line.length() > this->width)
        {
            this->width = line.length();
            if (line[line.length()-1] == '\n')
                --this->width;
        }
    }
    Position::w = this->width;
    Position::h = this->height;
}


size_t Wall::getLength() const
{
    return this->blocQty;
}


Wall::Wall(size_t width, size_t height)
    : width(width), height(height)
{
    this->blocQty = 0;
    for(size_t y = 0; y < height; y++){
        for(size_t x = 0; x < width; x++){
            if(y == 0 or y == height-1){
                addBloc(x, y);
            }
            else if(x == 0 or x == width - 1){
                addBloc(x, y);
            }
        }
    }
}

bool Wall::overlap(Position pos) const
{
    for(size_t i = 0; i < this->blocQty; i++)
        if (pos == this->blocs[i])
            return true;
    return false;
}

const Position& Wall::getBlocPos(size_t index) const
{
    return this->blocs[index];
}

size_t Wall::getBlocQty() const
{
    return this->blocQty;
}

void Wall::addBloc(Position pos)
{
    this->blocQty++;
    this->blocs.push_back(pos);
}

void Wall::addBloc(size_t x, size_t y)
{
    this->blocQty++;
    Position pos(x, y);
    this->blocs.push_back(pos);
}

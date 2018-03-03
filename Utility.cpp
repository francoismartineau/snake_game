/*
 * \file Utility.cpp
 * \date Oct 28, 2017
 * \author François Martineau
 */
#include "Utility.h"
#include <iostream>



bool Position::operator==(const Position & pos) const
{
    return (x == pos.x and y == pos.y);
}

std::ostream & operator<<(std::ostream & os, const Position & pos)
{
    os << "[" << pos.x << ", " << pos.y << "]";
    return os;
}

/*
 * \file Apple.cpp
 * \date Oct 28, 2017
 * \author François Martineau
 */
#include "Apple.h"



void Apple::setPosition(const Position & pos){
    m_position = pos;
}
const Position & Apple::getPosition(){
    return m_position;
}


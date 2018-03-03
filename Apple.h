/*
 * \file Apple.h
 * \date Oct 27, 2017
 * \author François Martineau
 */

#ifndef APPLE_H_
#define APPLE_H_
#include "Utility.h"

class Apple {
public:
    void setPosition(const Position & pos);
    const Position & getPosition();

private:
    Position m_position;
};



#endif /* APPLE_H_ */

#pragma once

#include "Position.h"

class Move
{
public:
    Move(void){};
    ~Move(void){};
    Position origin;
    Position destination;
    bool operator== (const Move& rhs)
    {
        return ((origin==rhs.origin)&&(destination==rhs.destination));
    }
};


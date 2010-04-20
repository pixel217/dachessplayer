#pragma once
class Position
{
public:
    Position(void){};
    ~Position(void){};
	unsigned char x:4;
	unsigned char y:4;
    bool operator== (const Position& rhs) const 
    {
        return ((x==rhs.x)&&(y==rhs.y));
    }
};


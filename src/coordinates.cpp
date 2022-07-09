#include <iostream>
#include "../include/coordinates.hpp"

//          Constructors and Destructor
Coordinates::Coordinates()
{
    _hit = false;
}
Coordinates::Coordinates(int y, int x)
{
    setCoor(y, x);
    _hit = false;
}
Coordinates::Coordinates(std::pair<int, int> coor)
{
    setCoor(coor);
    _hit = false;
}
Coordinates::~Coordinates()
{
}

//          Setters
void Coordinates::setCoor(int y, int x)
{
    _y = y;
    _x = x;
    return;
}
void Coordinates::setCoor(std::pair<int, int> coor)
{
    _y = coor.first;
    _x = coor.second;
    return;
}
void Coordinates::setHit(bool value)
{
    _hit = value;
    return;
}

//      Getter
int Coordinates::getY()
{
    return _y;
}
int Coordinates::getX()
{
    return _x;
}
std::pair<int, int> Coordinates::getCoor()
{
    return std::make_pair(_y, _x);
}
bool Coordinates::isHit()
{
    return _hit;
}
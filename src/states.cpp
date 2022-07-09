#include "../include/states.hpp"

//          Constructor and destructor
States::States()
{
}
States::~States()
{
}

//          Setters
void States::setPlaced(bool placed)
{
    _placed = placed;
}
void States::setDestroyed(bool destroyed)
{
    _destroyed = destroyed;
}
void States::setVertical(bool vertical)
{
    _vertical = vertical;
}

//          Getters
bool States::isPlaced()
{
    return _placed;
}
bool States::isDestroyed()
{
    return _destroyed;
}
bool States::isVertical()
{
    return _vertical;
}
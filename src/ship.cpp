#include "../include/ship.hpp"
#include <string>

Ship::Ship()
{
    _name = "";
    _length = 0;
}
Ship::Ship(mINI::INIStructure ini, int index)
{
    _name = (ini["SHIP_INFO"][std::to_string(index)]);
    _length = std::stoi(ini["SHIP_INFO"][_name]);

    _state.setPlaced(false);
    _state.setDestroyed(false);

    _horizontalLayot.push_back(ini["SHIP_INFO"]["LeftBlock"]);
    _verticalLayot.push_back(ini["SHIP_INFO"]["TopBlock"]);
    for (int i = 1; i < _length - 1; i++)
    {
        _horizontalLayot.push_back(ini["SHIP_INFO"]["MiddleBlock"]);
        _verticalLayot.push_back(ini["SHIP_INFO"]["MiddleBlock"]);
    }
    _horizontalLayot.push_back(ini["SHIP_INFO"]["RightBlock"]);
    _verticalLayot.push_back(ini["SHIP_INFO"]["BottomBlock"]);
}
Ship::~Ship()
{
}

int Ship::length()
{
    return _length;
}
std::string Ship::getLayout(int index)
{
    if (_state.isVertical())
    {
        return _verticalLayot[index];
    }
    else
    {
        return _horizontalLayot[index];
    }
}
std::string Ship::getName()
{
    return _name;
}
std::pair<int, int> Ship::getPosition(int index)
{
    return _position[index].getCoor();
}

bool Ship::isPlaced()
{
    return _state.isPlaced();
}
bool Ship::isDestroyed()
{
    return _state.isDestroyed();
}
bool Ship::isVertical()
{
    return _state.isVertical();
}

bool Ship::isHit(int index)
{
    return _position[index].isHit();
}

void Ship::gotHit(int index)
{

    _position[index].setHit(true);

    return;
}

void Ship::placeShipAt(int y, int x, bool isVertical)
{
    _state.setVertical(isVertical);

    Coordinates temp(y, x);
    _position.push_back(temp);

    for (int i = 0; i < _length - 1; ++i)
    {
        if (_state.isVertical())
        {
            y++;
        }
        else
        {
            x++;
        }
        temp.setCoor(y, x);
        temp.setHit(false);
        _position.push_back(temp);
    }
    _state.setPlaced(true);
    return;
}
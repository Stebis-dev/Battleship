#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ini.h"
#include "coordinates.hpp"
#include "states.hpp"

class Ship
{
private:
    std::string _name;
    int _length;

    std::vector<std::string> _horizontalLayot;
    std::vector<std::string> _verticalLayot;

    States _state;
    std::vector<Coordinates> _position;

public:
    Ship();
    Ship(mINI::INIStructure ini, int index);
    ~Ship();

    int length();
    std::string getLayout(int index);
    std::string getName();
    std::pair<int, int> getPosition(int index);

    bool isPlaced();
    bool isDestroyed();
    bool isVertical();

    bool isHit(int index);

    void gotHit(int index);

    void placeShipAt(int y, int x, bool isVertical);
};
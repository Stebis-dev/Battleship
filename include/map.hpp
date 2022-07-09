// Map class
#pragma once

#include <vector>
#include "cell.hpp"
#include "ship.hpp"
#include "ini.h"

class Map
{
private:
    int _y, _x;
    std::vector<std::vector<Cell>> _block;

    std::string _visualBackground;
    std::string _middleBlock;

    bool _visible;
    bool _spaceBetweenShip;

    std::string _shipColor;
    std::string _waterColor;
    std::string _hitColor;
    std::string _defaultColor;

public:
    //          Constructor and Destructor
    Map(mINI::INIStructure ini, bool isFog, std::string ownerName);
    ~Map();

    std::string show();
    void update();

    void select(int y, int x, bool IsVertical, int size, std::string color);

    int getMapY();
    int getMapX();

    int getCellValue(int i, int j);
    bool isCellHit(int i, int j);

    void setCell(int y, int x, int value);
    void setCell(int y, int x, std::string value);
    void setCell(int y, int x, bool value);
    void setVisibility(bool value);

    bool isShipExpansionEnabled();
};

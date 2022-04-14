// Map class
#ifndef MAP_H
#define MAP_H

#include <string>
#include "ship.h"
#include "ini.h"

class Map
{

protected:
    int x, y;
    bool **hitMap;
    int **infoMap;
    std::string **visualMap;

    bool isSpaceBetweenShips;

public:
    Map(mINI::INIStructure *ini);
    Map();
    ~Map();
    void allocatingMemory();

    int PlaceShip(Ship *a, const std::pair<int, int> possition, const bool vertical);
    void PlaceRandShips(mINI::INIStructure *ini, Ship *AI);

    std::string DisplayMap();
};

#endif
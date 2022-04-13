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

    bool isSpace;

public:
    Map(mINI::INIStructure ini);
    Map();
    ~Map();
    void allocatingMemory();

    int PlaceShip(Ship *a, std::pair<int, int> possition, bool vertical);
    void PlaceRandShips(Ship AI[5]);

    std::string DisplayMap();
};

#endif
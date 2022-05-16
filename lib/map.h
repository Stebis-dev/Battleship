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
    std::string background;

    int shipCount;
    bool isSpaceBetweenShips;

    std::string userShipColor;
    std::string enemyShipColor;
    std::string seaColor;
    std::string selectColor;

public:
    Map(mINI::INIStructure *ini);
    Map();
    ~Map();
    void allocatingMemory();

    int GetShipCount();
    int GetMapX();
    int GetMapY();

    int PlaceShip(Ship *a, const std::pair<int, int> possition, const bool vertical);
    void PlaceRandShips(mINI::INIStructure *ini, Ship *AI);

    std::string DisplayMap();
    std::string DisplayMap(int posX, int posY, bool vertical, int length);

    void updateMap(int **area);
};

#endif
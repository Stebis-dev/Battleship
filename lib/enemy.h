#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "map.h"
#include "ship.h"
#include "ini.h"

class Enemy : public Map
{
private:
    bool visible;

public:
    using Map::Map;
    // basicaly sets visibility
    void operator=(mINI::INIStructure *ini); // overloaded operator bc it is in requirements
    void PlaceRandShips(mINI::INIStructure *ini, Ship *AI);
    std::string DisplayMap();
};

#endif
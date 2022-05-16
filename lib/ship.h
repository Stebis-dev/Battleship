// Ship class
#ifndef SHIP_H
#define SHIP_H

#include <string>
#include "ini.h"

struct coordinates
{
    int x;
    int y;
    bool vertical;
};

class Ship
{
private:
    int shipLength;
    std::string type;
    std::string *hLayout;
    std::string *vLayout;
    bool placed;
    int damage;
    bool destroyed;
    coordinates c;

public:
    Ship(mINI::INIStructure *ini, int index);
    Ship();

    ~Ship();

    bool IsShipPlacedOnMap();
    void ShipPlacedOnMap(int x, int y, bool vertical);

    bool IsDestroyed();

    int length();

    void SetData(mINI::INIStructure *ini, int index);
    void SetVisuals(mINI::INIStructure *ini);

    std::string GetHLayout(int index);
    std::string GetVLayout(int index);

    void operator++();
};

#endif
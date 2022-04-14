// Ship class
#ifndef SHIP_H
#define SHIP_H

#include <string>
#include "ini.h"

class Ship
{
private:
    int shipLength;
    std::string type;
    std::string *hLayout;
    std::string *vLayout;
    bool placed;

public:
    Ship(mINI::INIStructure *ini, int index);
    Ship();

    ~Ship();

    bool IsShipPlacedOnMap();
    void ShipPlacedOnMap();

    int length();

    void SetData(mINI::INIStructure *ini, int index);
    void SetVisuals(mINI::INIStructure *ini);

    std::string GetHLayout(int index);
    std::string GetVLayout(int index);
};

#endif
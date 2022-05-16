#include <iostream>
#include <map>
#include <string>
#include "ship.h"

Ship::Ship(mINI::INIStructure *ini, int index)
{
    SetData(ini, index);
}
Ship::Ship() {}

Ship::~Ship() {}

bool Ship::IsShipPlacedOnMap()
{
    return placed;
}

void Ship::ShipPlacedOnMap(int x, int y, bool vertical)
{
    // starts count from 0
    c.x = x;
    c.y = y;
    c.vertical = vertical;
    placed = true;
    // std::cout << x << " " << y << " " << vertical << " " << shipLength << std::endl;
}
int Ship::length()
{
    return shipLength;
}

void Ship::SetData(mINI::INIStructure *ini, int index)
{
    std::string indexString = std::to_string(index);
    shipLength = stoi((*ini)["SHIP_INFO"][(*ini)["SHIP_INFO"][indexString]]);
    placed = false;
    vLayout = new std::string[shipLength];
    hLayout = new std::string[shipLength];
    SetVisuals(ini);
    damage = 0;
    destroyed = false;
}

void Ship::SetVisuals(mINI::INIStructure *ini)
{
    vLayout[0] = (*ini)["SHIP_INFO"]["TopBlock"];
    hLayout[0] = (*ini)["SHIP_INFO"]["LeftBlock"];
    for (int i = 1; i < shipLength - 1; i++)
    {
        vLayout[i] = (*ini)["SHIP_INFO"]["MiddleBlock"];
        hLayout[i] = (*ini)["SHIP_INFO"]["MiddleBlock"];
    }
    vLayout[shipLength - 1] = (*ini)["SHIP_INFO"]["BottomBlock"];
    hLayout[shipLength - 1] = (*ini)["SHIP_INFO"]["RightBlock"];
}

std::string Ship::GetHLayout(int index)
{
    return hLayout[index];
}
std::string Ship::GetVLayout(int index)
{
    return vLayout[index];
}
void Ship::operator++()
{
    damage++;
    if (damage == shipLength)
        destroyed = true;
    return;
}
bool Ship::IsDestroyed()
{
    return destroyed;
}

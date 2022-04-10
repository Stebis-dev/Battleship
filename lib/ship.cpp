#include "ship.h"
#include <string>
#include <map>
#include <iostream>

Ship::Ship(std::string name)
{
    SetData(name);
}
Ship::Ship() {}

Ship::~Ship() {}

bool Ship::IsShipPlaced()
{
    return placed;
}

void Ship::ShipPlaced()
{
    placed = true;
}
int Ship::length()
{
    return shipLength;
}

void Ship::SetData(std::string name)
{
    std::map<std::string, int> lengthByName;
    lengthByName = {
        {"Carrier", 5},
        {"Battleship", 4},
        {"Cruiser", 3},
        {"Submarine", 3},
        {"Destroyer", 2}};
    shipLength = lengthByName[name];
    placed = false;
    SetVisuals();
}

void Ship::SetVisuals()
{
    vLayout[0] = "⛰";
    hLayout[0] = "◁";
    for (int i = 1; i < shipLength - 1; i++)
    {
        vLayout[i] = "⛝";
        hLayout[i] = "⛝";
    }
    vLayout[shipLength - 1] = "⛊";
    hLayout[shipLength - 1] = "▷";
}

std::string Ship::GetHLayout(int index)
{
    return hLayout[index];
}
std::string Ship::GetVLayout(int index)
{
    return vLayout[index];
}
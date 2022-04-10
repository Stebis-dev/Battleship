// Ship class
#ifndef SHIP_H
#define SHIP_H

#include <string>

class Ship
{
private:
    int shipLength;
    std::string type;
    std::string hLayout[5];
    std::string vLayout[5];
    bool placed;

public:
    Ship(std::string name);
    Ship();

    ~Ship();

    bool IsShipPlaced();
    void ShipPlaced();

    int length();

    void SetData(std::string name);
    void SetVisuals();

    std::string GetHLayout(int index);
    std::string GetVLayout(int index);
};

#endif
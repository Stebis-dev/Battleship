// Coordinate class
#pragma once

#include <iostream>

class Coordinates
{
private:
    int _y;
    int _x;
    bool _hit;

public:
    //          Constructor and Destructor
    Coordinates();
    Coordinates(int y, int x);
    Coordinates(std::pair<int, int> coor);
    ~Coordinates();

    //          Setters
    void setCoor(int y, int x);
    void setCoor(std::pair<int, int> coor);

    void setHit(bool value);

    //          Getters
    int getY();
    int getX();
    std::pair<int, int> getCoor();
    bool isHit();
};
// projectile class
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <string>
#include <utility>
#include "ini.h"

class ProjectileInfo
{
private:
    int X, Y;
    std::pair<int, int> cord;
    std::pair<int, int> projSize;
    int **area;

public:
    ProjectileInfo(int x, int y, mINI::INIStructure *ini);
    ProjectileInfo();
    ~ProjectileInfo();
    void PopulateArea(int x, int y);
    int **GetArea();
};

#endif
#include "projectile.h"

ProjectileInfo::ProjectileInfo(int x, int y, mINI::INIStructure *ini)
{
    X = stoi((*ini)["Map"]["x"]);
    Y = stoi((*ini)["Map"]["y"]);

    projSize.first = x;
    projSize.second = y;

    area = new int *[this->Y];
    for (int i = 0; i < Y + y; i++)
    {
        area[i] = new int[X + x];
    }
}
ProjectileInfo::ProjectileInfo() {}

ProjectileInfo::~ProjectileInfo()
{
    for (int i = 0; i < projSize.first; i++)
    {
        delete[] area[i];
    }
    delete[] area;
}
void ProjectileInfo::PopulateArea(int x, int y)
{
    for (int i = 0; i < Y; i++)
    {
        for (int ii = 0; ii < X; ii++)
        {
            area[i][ii] = 0;
        }
    }

    for (int i = y; i < y + projSize.second; i++)
    {
        for (int ii = x; ii < x + projSize.first; ii++)
        {
            area[i][ii] = 1;
        }
    }
    return;
}
int **ProjectileInfo::GetArea()
{
    return area;
}
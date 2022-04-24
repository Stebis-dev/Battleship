#include "enemy.h"
#include "utilityAddOns.h"

void Enemy::PlaceRandShips(mINI::INIStructure *ini, Ship *AI)
{
    int c, xPos, yPos, shipCount = stoi((*ini)["SHIP_INFO"]["ShipCount"]);
    for (int i = 1; i <= shipCount; i++)
    {
        AI->SetData(ini, i);
        while (true)
        {
            c = rand() % 2;
            if (c)
            {
                xPos = rand() % x + 1;
                yPos = rand() % (y - AI->length() + 1) + 1;
            }
            else
            {
                yPos = rand() % y + 1;
                xPos = rand() % (x - AI->length() + 1) + 1;
            }
            if (PlaceShip(AI, std::make_pair(xPos, yPos), c) == 0)
                break;
        }
        AI++;
    }
    return;
}
std::string Enemy::DisplayMap()
{
    std::string savedMap = "";
    savedMap += "";
    for (int i = 0; i < y; ++i)
    {
        for (int ii = 0; ii < x; ++ii)
        {
            if (visible)
            {
                savedMap += visualMap[i][ii];
            }
            else if (infoMap[i][ii] < 0)
            {
                savedMap += visualMap[i][ii];
            }
            else
            {
                savedMap += background;
            }

            savedMap += " ";
        }
        savedMap += "\n";
    }
    return savedMap;
}
void Enemy::operator=(mINI::INIStructure *ini)
{
    visible = toBoolean((*ini)["Map"]["Visible"]);
}

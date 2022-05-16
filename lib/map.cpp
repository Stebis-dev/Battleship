#include "map.h"
#include "utilityAddOns.h"

Map::Map(mINI::INIStructure *ini)
{
    x = stoi((*ini)["Map"]["x"]);
    y = stoi((*ini)["Map"]["y"]);
    background = (*ini)["Map"]["Background"];
    isSpaceBetweenShips = toBoolean((*ini)["Map"]["Space"]);

    std::string cFront = "\x1b[";
    std::string cEnd = "m";

    userShipColor = cFront + (*ini)["SHIP_INFO"]["UserShipColor"] + cEnd;
    enemyShipColor = cFront + (*ini)["SHIP_INFO"]["EnemyShipColor"] + cEnd;
    seaColor = cFront + (*ini)["SHIP_INFO"]["SeaColor"] + cEnd;
    selectColor = cFront + (*ini)["SHIP_INFO"]["SelectColor"] + cEnd;

    shipCount = 0;
    allocatingMemory();
}
Map::Map() {}

Map::~Map()
{
    for (int i = 0; i < y; i++)
    {
        delete[] hitMap[i];
        delete[] infoMap[i];
        delete[] visualMap[i];
    }
    delete[] hitMap;
    delete[] infoMap;
    delete[] visualMap;
}

void Map::allocatingMemory()
{
    // allocating dynamic memory;
    hitMap = new bool *[y];
    infoMap = new int *[y];
    visualMap = new std::string *[y];

    for (int i = 0; i < y; ++i)
    {
        hitMap[i] = new bool[x];
        infoMap[i] = new int[x];
        visualMap[i] = new std::string[x];
    }

    // initializing
    for (int i = 0; i < y; ++i)
        for (int ii = 0; ii < x; ++ii)
        {
            hitMap[i][ii] = false;
            infoMap[i][ii] = 0;
            visualMap[i][ii] = background;
        }
}
int Map::GetShipCount()
{
    return this->shipCount;
}
int Map::GetMapX()
{
    return this->x;
}
int Map::GetMapY()
{
    return this->y;
}

int Map::PlaceShip(Ship *a, const std::pair<int, int> possition, const bool vertical)
{
    if (a->IsShipPlacedOnMap())
        return -2;

    // Alocates memory to temporary map
    int **tempInfoMap = new int *[y + 2];
    for (int i = 0; i < y + 2; i++)
        tempInfoMap[i] = new int[x + 2];

    // Set temporary map to zero value
    for (int i = 0; i < y + 2; i++)
        for (int ii = 0; ii < x + 2; ii++)
            tempInfoMap[i][ii] = 0;

    // Information copy of main map
    for (int i = 0; i < y; i++)
        for (int ii = 0; ii < x; ii++)
            tempInfoMap[i + 1][ii + 1] = infoMap[i][ii];

    int xPos = possition.first;
    int yPos = possition.second;

    // Checks if ship can be placed on a map
    for (int i = 0; i < a->length(); i++)
    {
        if (vertical)
        {
            if (tempInfoMap[yPos + i][xPos] != 0)
                return -1;
        }
        else
        {
            if (tempInfoMap[yPos][xPos + i] != 0)
                return -1;
        }
    }
    // If there is space between ships, than the space is filled to be ingored for next ship placement
    if (isSpaceBetweenShips)
    {
        for (int ii = 0; ii < 3; ii++)
            for (int i = 0; i < a->length() + 2; i++)
            {
                if (vertical)
                {
                    if (tempInfoMap[yPos + i - 1][xPos + ii - 1] == 0)
                        tempInfoMap[yPos + i - 1][xPos + ii - 1] = 1;
                }
                else
                {
                    if (tempInfoMap[yPos + ii - 1][xPos + i - 1] == 0)
                        tempInfoMap[yPos + ii - 1][xPos + i - 1] = 1;
                }
            }
    }

    yPos--;
    xPos--;
    // Ship placement on the maps
    for (int i = 0; i < a->length(); i++)
    {
        if (vertical)
        {
            tempInfoMap[yPos + i + 1][xPos + 1] = a->length();
            infoMap[yPos + i][xPos] = a->length();
            visualMap[yPos + i][xPos] = a->GetVLayout(i);
        }
        else
        {
            tempInfoMap[yPos + 1][xPos + i + 1] = a->length();
            infoMap[yPos][xPos + i] = a->length();
            visualMap[yPos][xPos + i] = a->GetHLayout(i);
        }
    }
    this->shipCount++;
    for (int i = 0; i < y; i++)
        for (int ii = 0; ii < x; ii++)
            infoMap[i][ii] = tempInfoMap[i + 1][ii + 1];

    a->ShipPlacedOnMap(xPos, yPos, vertical);
    for (int i = 0; i < y + 2; i++)
        delete[] tempInfoMap[i];
    delete[] tempInfoMap;

    return 0;
}
void Map::PlaceRandShips(mINI::INIStructure *ini, Ship *AI)
{
    int c, xPos, yPos;
    int shipCount = stoi((*ini)["SHIP_INFO"]["ShipCount"]);

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
std::string Map::DisplayMap()
{
    std::string savedMap = "";
    savedMap += "";
    for (int i = 0; i < y; ++i)
    {
        for (int ii = 0; ii < x; ++ii)
        {

            if (infoMap[i][ii] > 1)
            {
                savedMap += userShipColor;
            }
            else
            {
                savedMap += seaColor;
            }
            savedMap += visualMap[i][ii];
            savedMap += " \x1b[0m";
        }
        savedMap += "\n";
    }
    return savedMap;
}
std::string Map::DisplayMap(int posX, int posY, bool vertical, int length)
{
    std::string savedMap = "";
    savedMap += "";
    int temp = 0;
    for (int i = 0; i < this->y; ++i)
    {
        for (int ii = 0; ii < this->x; ++ii)
        {
            if (vertical && ii == posX + temp && i == posY && temp != length)
            {
                savedMap += selectColor;
                temp++;
            }
            else if (i == posY + temp && ii == posX && temp != length)
            {
                savedMap += selectColor;
                temp++;
            }
            else if (infoMap[i][ii] > 1)
            {
                savedMap += userShipColor;
            }
            else
            {
                savedMap += seaColor;
            }
            savedMap += visualMap[i][ii];
            savedMap += " \x1b[0m";
        }
        savedMap += "\n";
    }
    return savedMap;
}
void Map::updateMap(int **area)
{
    for (int i = 0; i < this->y; ++i)
    {
        for (int ii = 0; ii < this->x; ++ii)
        {
            if (area[i][ii] == 1)
                hitMap[i][ii] = true;
        }
    }
    return;
}

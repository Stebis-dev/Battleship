#include "map.h"
#include "ship.h"
#include <string>
#include <iostream>
#include <time.h>

bool toBoolean(std::string str)
{
    if (str == "True" || str == "TRUE" || str == "true")
        return true;
    else
        return false;
}

Map::Map(mINI::INIStructure ini)
{
    x = stoi(ini["Map"]["x"]);
    y = stoi(ini["Map"]["y"]);
    isSpace = toBoolean(ini["Map"]["Space"]);
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
            visualMap[i][ii] = "·";
        }
}
int Map::PlaceShip(Ship *a, std::pair<int, int> possition, bool vertical)
{
    if (a->IsShipPlaced())
        return -2;

    int **tempInfoMap = new int *[y + 2];
    for (int i = 0; i < y + 2; i++)
        tempInfoMap[i] = new int[x + 2];

    for (int i = 0; i < y + 2; i++)
        for (int ii = 0; ii < x + 2; ii++)
            tempInfoMap[i][ii] = 0;

    for (int i = 0; i < y; i++)
    {
        for (int ii = 0; ii < x; ii++)
        {
            tempInfoMap[i + 1][ii + 1] = infoMap[i][ii];
            // std::cout << tempInfoMap[i][ii] << " ";
        }
        // std::cout << "\n";
    }

    int posX = possition.first;
    int posY = possition.second;

    for (int i = 0; i < a->length(); i++)
    {
        if (vertical)
        {
            if (tempInfoMap[posY + i][posX] != 0)
                return -1;
        }
        else
        {
            if (tempInfoMap[posY][posX + i] != 0)
                return -1;
        }
    }

    for (int ii = 0; ii < 3; ii++)
    {
        for (int i = 0; i < a->length() + 2; i++)
        {
            if (vertical)
            {
                if (tempInfoMap[posY + i - 1][posX + ii - 1] == 0)
                    tempInfoMap[posY + i - 1][posX + ii - 1] = 1;
            }
            else
            {
                if (tempInfoMap[posY + ii - 1][posX + i - 1] == 0)
                    tempInfoMap[posY + ii - 1][posX + i - 1] = 1;
            }
        }
    }
    posY--;
    posX--;

    for (int i = 0; i < a->length(); i++)
    {
        if (vertical)
        {
            tempInfoMap[posY + i + 1][posX + 1] = a->length();
            infoMap[posY + i][posX] = a->length();
            visualMap[posY + i][posX] = a->GetVLayout(i);
        }
        else
        {
            tempInfoMap[posY + 1][posX + i + 1] = a->length();
            infoMap[posY][posX + i] = a->length();
            visualMap[posY][posX + i] = a->GetHLayout(i);
        }
    }

    for (int i = 0; i < y; i++)
        for (int ii = 0; ii < x; ii++)
            infoMap[i][ii] = tempInfoMap[i + 1][ii + 1];

    // for (int i = 0; i < y + 2; i++)
    // {
    //     for (int ii = 0; ii < x + 2; ii++)
    //     {
    //         std::cout << tempInfoMap[i][ii] << " ";
    //     }
    //     std::cout << "\n";
    // }
    a->ShipPlaced();
    for (int i = 0; i < y + 2; i++)
        delete[] tempInfoMap[i];

    delete[] tempInfoMap;

    return 0;
}
void Map::PlaceRandShips(Ship AI[5])
{
    std::string shipType[6] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};

    int c, a, b;
    for (int i = 0; i < 5; i++)
    {
        AI[i].SetData(shipType[i]);
        while (true)
        {
            c = rand() % 2;
            if (c)
            {
                a = rand() % x + 1;
                b = rand() % (y - AI[i].length() + 1) + 1;
            }
            else
            {
                b = rand() % y + 1;
                a = rand() % (x - AI[i].length() + 1) + 1;
            }
            if (PlaceShip(&AI[i], std::make_pair(a, b), c) == 0)
                break;
        }
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
            if (infoMap[i][ii] == -5)
            {
                savedMap += "-";
            }
            else
            {
                savedMap += visualMap[i][ii];
                // savedMap += std::to_string(infoMap[i][ii]);
            }
            // cout << visualMap[i][ii];
            savedMap += " ";
        }
        savedMap += "\n";
    }
    return savedMap;
}

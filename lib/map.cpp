#include "map.h"
#include "ship.h"
#include <string>

Map::Map(mINI::INIStructure ini)
{
    x = stoi(ini["Map"]["x"]);
    y = stoi(ini["Map"]["y"]);
    Space = toBoolean(ini["Map"]["Space"]);
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

    possition.first--;
    possition.second--;
    for (int i = 0; i < a->length(); i++)
    {
        if (vertical)
        {
            if (infoMap[possition.first + i][possition.second] != 0 || possition.first + i >= y)
                return -1;
        }
        else
        {
            if (infoMap[possition.first][possition.second + i] != 0 || possition.second + i >= x)
                return -1;
        }
    }

    for (int i = 0; i < a->length(); i++)
    {
        if (vertical)
        {
            infoMap[possition.first + i][possition.second] = a->length();
            visualMap[possition.first + i][possition.second] = a->GetVLayout(i);
        }
        else
        {
            infoMap[possition.first][possition.second + i] = a->length();
            visualMap[possition.first][possition.second + i] = a->GetHLayout(i);
        }
    }
    a->ShipPlaced();
    return 0;
}
void Map::PlaceRandShips(Ship AI[5])
{
    std::string shipType[6] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};

    for (int i = 0; i < 5; i++)
    {
        AI[i].SetData(shipType[i]);
        while (true)
        {
            int c = rand() % 2, a, b;
            if (c)
            {
                a = rand() % (x - AI[i].length()) + 1;
                b = rand() % y + 1;
            }
            else
            {
                a = rand() % x + 1;
                b = rand() % (y - AI[i].length()) + 1;
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
            }
            //  savedMap += to_string(infoMap[i][ii]);
            // cout << visualMap[i][ii];
            savedMap += " ";
        }
        savedMap += "\n";
    }
    return savedMap;
}

bool toBoolean(std::string str)
{
    if (str == "True" || str == "TRUE" || str == "true")
        return true;
    else
        return false;
}
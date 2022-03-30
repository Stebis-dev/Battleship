#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <time.h>

using namespace std;

class Ship
{
private:
    int shipLength;
    char type;
    char hLayout[5];
    char vLayout[5];
    bool placed;

public:
    Ship(string name)
    {
        SetData(name);
    }
    Ship()
    {
    }
    ~Ship()
    {
    }
    bool IsPlaced()
    {
        return placed;
    }
    void Placed()
    {
        placed = true;
    }
    int length()
    {
        return shipLength;
    }
    void SetData(string name)
    {
        if (name == "Carrier")
        {
            shipLength = 5;
        }
        else if (name == "Battleship")
        {
            shipLength = 4;
        }
        else if (name == "Cruiser")
        {
            shipLength = 3;
        }
        else if (name == "Submarine")
        {
            shipLength = 3;
        }
        else if (name == "Destroyer")
        {
            shipLength = 2;
        }
        placed = false;
        SetVisuals();
    }
    void SetVisuals()
    {
        vLayout[0] = '^';
        hLayout[0] = '<';
        for (int i = 1; i < shipLength - 1; i++)
        {
            vLayout[i] = 219;
            hLayout[i] = 254;
        }
        vLayout[shipLength - 1] = 'v';
        hLayout[shipLength - 1] = '>';
    }
    char GetHLayout(int index)
    {
        return hLayout[index];
    }
    char GetVLayout(int index)
    {
        return vLayout[index];
    }
    void test()
    {
        for (int i = 0; i < shipLength; i++)
        {
            cout << hLayout[i];
        }
        cout << endl;

        for (int i = 0; i < shipLength; i++)
        {
            cout << vLayout[i] << '\n';
        }
    }
};
class Map
{
protected:
    int x, y;
    bool **hitMap;
    int **infoMap;
    char **visualMap;

public:
    Map(int a, int b) : x(a), y(b)
    {
        allocatingMemory();
    }
    Map() {}
    void allocatingMemory()
    {
        // allocating dynamic memory;
        hitMap = new bool *[y];
        infoMap = new int *[y];
        visualMap = new char *[y];

        for (int i = 0; i < y; ++i)
        {
            hitMap[i] = new bool[x];
            infoMap[i] = new int[x];
            visualMap[i] = new char[x];
        }

        // initializing
        for (int i = 0; i < y; ++i)
            for (int ii = 0; ii < x; ++ii)
            {
                hitMap[i][ii] = false;
                infoMap[i][ii] = 0;
                // visualMap[i][ii] = 254;
                visualMap[i][ii] = 250;
            }
    }
    ~Map()
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
    int PlaceShip(Ship *a, pair<int, int> possition, bool vertical)
    {
        if (a->IsPlaced())
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
        a->Placed();
        return 0;
    }
    string DisplayMap()
    {
        string savedMap = "";
        for (int i = 0; i < y; ++i)
        {
            for (int ii = 0; ii < x; ++ii)
            {
                savedMap += visualMap[i][ii];
                // savedMap += to_string(infoMap[i][ii]);
                savedMap += " ";
            }
            savedMap += '\n';
        }
        return savedMap;
    }
};
class MistyMap : public Map
{
public:
    MistyMap(int a, int b)
    {
        x = a;
        y = b;
        allocatingMemory();
    }
    void randPlace(Ship AI[5])
    {
        string shipType[6] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
        for (int i = 0; i < y; ++i)
            for (int ii = 0; ii < x; ++ii)
                visualMap[i][ii] = 0;

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
                if (PlaceShip(&AI[i], make_pair(a, b), c) == 0)
                    break;
            }
        }
        if (false)
        {
            for (int i = 0; i < y; ++i)
                for (int ii = 0; ii < x; ++ii)
                {
                    visualMap[i][ii] = 250;
                }
        }
        return;
    }
};
int main()
{
    srand(time(0));

    Ship *userShips = new Ship[5];
    Ship *enemyShips = new Ship[5];
    Map user(10, 10);
    MistyMap enemy(10, 10);

    enemy.randPlace(enemyShips);

    userShips[0].SetData("Carrier");
    userShips[1].SetData("Battleship");
    userShips[2].SetData("Submarine");

    // sending pointer so that would send a whole class but just small value to a functuon. . ..  IDK if it affected performence
    user.PlaceShip(&userShips[0], make_pair(2, 2), true);
    user.PlaceShip(&userShips[1], make_pair(2, 3), true);
    user.PlaceShip(&userShips[2], make_pair(8, 10), true);

    cout << enemy.DisplayMap() << '\n';

    cout << user.DisplayMap();

    delete[] userShips, enemyShips;
    return 0;
}
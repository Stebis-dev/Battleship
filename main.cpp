#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

class Ship
{
private:
    int length;
    char type;
    char hLayout[5];
    char vLayout[5];
    static int count;

public:
    Ship(string name)
    {
        count++;
        SetData(name);
        SetVisuals();
    }
    Ship() {}
    void SetData(string name)
    {
        if (name == "Carrier")
        {
            length = 5;
        }
        else if (name == "Battleship")
        {
            length = 4;
        }
        else if (name == "Cruiser")
        {
            length = 3;
        }
        else if (name == "Submarine")
        {
            length = 3;
        }
        else if (name == "Destroyer")
        {
            length = 2;
        }
        SetVisuals();
    }
    void SetVisuals()
    {
        vLayout[0] = '^';
        hLayout[0] = '<';
        for (int i = 1; i < length - 1; i++)
        {
            vLayout[i] = 219;
            hLayout[i] = 254;
        }
        vLayout[length - 1] = 'v';
        hLayout[length - 1] = '>';
    }
    void test()
    {
        for (int i = 0; i < length; i++)
        {
            cout << hLayout[i];
        }
        cout << endl;

        for (int i = 0; i < length; i++)
        {
            cout << vLayout[i] << '\n';
        }
    }
};
class Map
{
private:
    int x, y;
    bool **hitMap;
    int **infoMap;
    char **visualMap;

public:
    Map(int a, int b) : x(a), y(b)
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
        for (int i = 0; i < x; ++i)
            for (int ii = 0; ii < y; ++ii)
            {
                hitMap[i][ii] = false;
                infoMap[i][ii] = 0;
                visualMap[i][ii] = 254;
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
    void PlaceShip(Ship &a, pair<int, int> possition)
    {
    }
    string DisplayMap()
    {
        string savedMap = "";
        for (int i = 0; i < x; ++i)
        {
            for (int ii = 0; ii < y; ++ii)
            {
                savedMap += visualMap[i][ii];
                savedMap += " ";
            }
            savedMap += '\n';
        }
        return savedMap;
    }
};

int main()
{
    Ship *userShips = new Ship[5];
    userShips[0].SetData("Carrier");

    Map user(10, 10);
    user.PlaceShip(userShips[0], make_pair(0, 0));
    cout << user.DisplayMap();

    delete[] userShips;
    return 0;
}
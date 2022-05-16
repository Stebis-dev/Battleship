#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include "lib/utilityAddOns.h"

#define VERTICAL true
#define HORIZONTAL false

#define DEBUG false
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_R 82
#define KEY_r 114
#define KEY_Q 81
#define KEY_q 113
#define KEY_E 69
#define KEY_e 101
#define KEY_W 87
#define KEY_w 119
#define KEY_ESCAPE 27

using namespace std;

int main()
{
    // Config file data variable
    mINI::INIFile file("config.INI");
    mINI::INIStructure ini;
    file.read(ini);

    //

    srand(time(0));
    system("chcp 65001");
    system("cls");

    int shipCount = stoi(ini["SHIP_INFO"]["ShipCount"]);

    Ship *userShips = new Ship[shipCount];
    Ship *enemyShips = new Ship[shipCount];
    Map user(&ini);
    Enemy enemy(&ini);
    enemy = &ini; // sets visible

    // Places enemy ships and also populates with ships
    enemy.PlaceRandShips(&ini, enemyShips);
    // populates wiht ships
    for (int i = 1; i <= shipCount; i++)
        userShips[i].SetData(&ini, i);
    //

    cout << enemy.DisplayMap() + "\n\n" + user.DisplayMap() << endl;

    int keyPress, x = 0, y = 0, tempShipIndex = 1;
    bool tempVertical = true, endLoop = false;
    while (true)
    {
        if (endLoop)
            break;

        switch ((keyPress = _getch()))
        {
        case KEY_ESCAPE:
            endLoop = true;
            break;
        case KEY_UP:
            if (y - 1 >= 0)
                y--;
            break;
        case KEY_DOWN:
            if (tempVertical && y + 1 < stoi(ini["MAP"]["y"]))
                y++;
            if (!tempVertical && y + userShips[tempShipIndex].length() < stoi(ini["MAP"]["y"]))
                y++;
            break;
        case KEY_LEFT:
            if (x - 1 >= 0)
                x--;
            break;
        case KEY_RIGHT:
            if (!tempVertical && x + 1 < stoi(ini["MAP"]["x"]))
                x++;
            if (tempVertical && x + userShips[tempShipIndex].length() + 1 <= stoi(ini["MAP"]["x"]))
                x++;
            break;

        case KEY_r:
        case KEY_R:

            if (tempVertical)
            {
                if (y + userShips[tempShipIndex].length() <= stoi(ini["MAP"]["y"]))
                {
                    tempVertical = false;
                }
            }
            else
            {
                if (x + userShips[tempShipIndex].length() <= stoi(ini["MAP"]["x"]))
                {
                    tempVertical = true;
                }
            }
            break;
        case KEY_ENTER:
            if (user.PlaceShip(&userShips[tempShipIndex], make_pair(x + 1, y + 1), !tempVertical) == 0)
                tempShipIndex++;
            break;
        default:
            break;
        }
        // if every ship is placed than breaks out of loop
        for (int i = 1; i <= shipCount; i++)
        {
            if (userShips[i].IsShipPlacedOnMap())
            {
                endLoop = true;
            }
            else
            {
                endLoop = false;
            }
        }
        // -------draw the map
        string displayInformation = "";

        displayInformation += "\033[2J\033[1;1H"; // clears the console
        displayInformation += enemy.DisplayMap();
        displayInformation += "\n\n";

        displayInformation += user.DisplayMap(x, y, tempVertical, userShips[tempShipIndex].length());
        displayInformation += "\n";
        cout << displayInformation;

        //-------------
    }
    cout << "\033[2J\033[1;1H" << enemy.DisplayMap() + "\n\n" + user.DisplayMap() << "  \n";

    ProjectileInfo singleShot(1, 1, &ini);
    ProjectileInfo bigShot(3, 3, &ini);
    ProjectileInfo *shots = new ProjectileInfo[2];
    shots[0] = singleShot;
    shots[1] = bigShot;
    x = 3;
    y = 3;
    endLoop = false;
    int selectedShotType = 0; // 0 - single | 1 - big

    while (true)
    {
        if (endLoop)
            break;
        switch ((keyPress = _getch()))
        {
        case KEY_ESCAPE:
            endLoop = true;
            break;
        case KEY_UP:
            if (y - 1 >= 0)
                y--;
            break;
        case KEY_DOWN:
            if (y + 1 < stoi(ini["MAP"]["y"]))
                y++;
            break;
        case KEY_LEFT:
            if (x - 1 >= 0)
                x--;
            break;
        case KEY_RIGHT:
            if (x + 1 < stoi(ini["MAP"]["x"]))
                x++;
            break;
        case KEY_Q:
        case KEY_q:
            if (selectedShotType == 0)
            {
                selectedShotType = 1;
            }
            else
            {
                selectedShotType = 0;
            }
            break;
        case KEY_ENTER:
            cout << "enter\n";
            enemy.updateMap(shots[selectedShotType].GetArea());
            break;
        default:
            break;
        }
        singleShot.PopulateArea(x, y);
        bigShot.PopulateArea(x, y);

        string displayInformation = "";

        displayInformation += "\033[2J\033[1;1H"; // clears the console
        // displayInformation += enemy.DisplayMap(x, y, singleShot.GetArea());
        displayInformation += enemy.DisplayMap(x, y, shots[selectedShotType].GetArea());
        displayInformation += "\n\n";

        displayInformation += user.DisplayMap();
        displayInformation += "\n Q - changes shot type\n";
        cout << displayInformation;
    }

    cout << "closing . . .\n";
    delete[] userShips, enemyShips;
    return 0;
}
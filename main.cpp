#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "lib/ship.h"
#include "lib/map.h"
#include "lib/ini.h"

using namespace std;

int main()
{
    mINI::INIFile file("config.INI");
    mINI::INIStructure ini;
    file.read(ini);
    //

    const bool VERTICAL = true, HORIZONTAL = false;
    srand(time(0));
    system("chcp 65001");

    Ship *userShips = new Ship[5];
    Ship *enemyShips = new Ship[5];
    Map user(ini), enemy(ini);

    enemy.PlaceRandShips(enemyShips);

    userShips[0].SetData("Carrier");
    userShips[1].SetData("Battleship");
    userShips[2].SetData("Submarine");

    // sending pointer so that would send a whole class but just small value to a functuon. . ..  IDK if it affected performence
    user.PlaceShip(&userShips[0], make_pair(2, 2), VERTICAL);
    user.PlaceShip(&userShips[1], make_pair(2, 3), VERTICAL);
    user.PlaceShip(&userShips[2], make_pair(8, 10), VERTICAL);

    cout << enemy.DisplayMap() + "\n\n" + user.DisplayMap() << endl;

    delete[] userShips, enemyShips;
    return 0;
}
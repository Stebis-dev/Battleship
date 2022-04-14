#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "lib/ship.h"
#include "lib/map.h"
#include "lib/ini.h"

#define VERTICAL true
#define HORIZONTAL false

using namespace std;

int main()
{
    mINI::INIFile file("config.INI");
    mINI::INIStructure ini;
    file.read(ini);

    //

    srand(time(0));
    system("chcp 65001");
    Ship *userShips = new Ship[5];
    Ship *enemyShips = new Ship[5];
    Map user(&ini), enemy(&ini);

    enemy.PlaceRandShips(&ini, enemyShips);

    userShips[0].SetData(&ini, 1);
    userShips[1].SetData(&ini, 2);
    userShips[2].SetData(&ini, 3);

    // sending  pointer so that would send a whole class but just small value to a functuon. . ..  IDK if it affected performence
    user.PlaceShip(&userShips[0], make_pair(1, 1), HORIZONTAL);
    user.PlaceShip(&userShips[1], make_pair(3, 3), VERTICAL);
    user.PlaceShip(&userShips[2], make_pair(8, 7), HORIZONTAL);

    cout << enemy.DisplayMap() + "\n\n" + user.DisplayMap() << endl;

    delete[] userShips, enemyShips;
    return 0;
}
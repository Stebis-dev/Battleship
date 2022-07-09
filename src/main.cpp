#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "../include/ship.hpp"
#include "../include/map.hpp"
#include "../include/ini.h"

#define DEBUG false
#define SLEEP 1200

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ENTER = 13;
const int KEY_R = 82;
const int KEY_r = 114;
const int KEY_Q = 81;
const int KEY_q = 113;
const int KEY_E = 69;
const int KEY_e = 101;
const int KEY_W = 87;
const int KEY_w = 119;
const int KEY_ESCAPE = 27;

bool isFileInDirectory(std::string fileName)
{
    std::ifstream data(fileName);
    if (data.is_open())
    {
        data.close();
        return true;
    }
    return false;
}

void clearLines(int lineNumber)
{
    std::cout << "\033[" << lineNumber << "A";
    std::string tempDisplay = "";
    for (int j = 0; j < lineNumber; ++j)
    {
        for (int i = 0; i < 60; ++i)
        {
            tempDisplay += " ";
        }
        tempDisplay += "\n";
    }
    std::cout << tempDisplay;
    std::cout << "\033[" << lineNumber << "A";
}

bool isGeneratedCoordinatesValid(Map entity, Ship entityShip, int genY, int genX, int genIsvertical)
{
    // creates 2d dynamic array
    int tempMapY = entity.getMapY() + 2;
    int tempMapX = entity.getMapX() + 2;

    int **infoMap = new int *[tempMapY];
    for (int i = 0; i < tempMapY; ++i)
    {
        infoMap[i] = new int[tempMapX];
        for (int j = 0; j < tempMapX; ++j)
        {
            infoMap[i][j] = 0;
        }
    }
    //----

    // Copies maps intiger values to its temp map
    for (int i = 0; i < entity.getMapY(); ++i)
    {
        for (int j = 0; j < entity.getMapX(); ++j)
        {
            infoMap[i + 1][j + 1] = entity.getCellValue(i, j);
        }
    }
    //----

    genY++;
    genX++;

    // If generated coordinates are available
    // if ships cannot touch
    if (entity.isShipExpansionEnabled())
    {
        int tempShipLenght = entityShip.length() + 2;
        int offsetGenY = genY - 1, offsetGenX = genX - 1;

        for (int i = 0; i < tempShipLenght; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (genIsvertical)
                {
                    if (infoMap[offsetGenY + i][offsetGenX + j] > 0)
                    {
                        return false;
                    }
                }
                else
                {
                    if (infoMap[offsetGenY + j][offsetGenX + i] > 0)
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < entityShip.length(); ++i)
        {
            if (genIsvertical)
            {
                if (infoMap[genY + i][genX] > 0)
                {
                    return false;
                }
            }
            else
            {
                if (infoMap[genY][genX + i] > 0)
                {
                    return false;
                }
            }
        }
    }
    //----
    return true;
}

bool placeShipRandom(Map &entity, Ship &entityShip)
{
    bool genIsVertical;
    int genX, genY;
    int limit = 0;

    while (true)
    {
        genIsVertical = rand() % 2;
        if (genIsVertical)
        {
            genY = rand() % (entity.getMapY() - entityShip.length() + 1);
            genX = rand() % entity.getMapX();
        }
        else
        {
            genY = rand() % entity.getMapY();
            genX = rand() % (entity.getMapX() - entityShip.length() + 1);
        }
        if (isGeneratedCoordinatesValid(entity, entityShip, genY, genX, genIsVertical))
        {
            // Populates ship with ships place coordinates
            entityShip.placeShipAt(genY, genX, genIsVertical); // y, x, isVertical
            for (int i = 0; i < entityShip.length(); ++i)
            {
                // Draws ship on the map
                std::pair<int, int> tempCoor = entityShip.getPosition(i);
                entity.setCell(tempCoor.first, tempCoor.second, entityShip.length());
                entity.setCell(tempCoor.first, tempCoor.second, entityShip.getLayout(i));
                // entity.setCell(tempCoor.first, tempCoor.second, false);
                //----
            }
            // Ship was able to be placed
            return true;
        }
        else
        {
            limit++;
            if (limit >= 1000)
            {
                return false;
            }
            //! set limit for ship placing. To see diffrence between if you cannot actualy place ship or it just bad generated coordinate
        }
    }
    return false;
}

bool shotRegister(std::vector<Ship> &entityFleet, int inpY, int inpX)
{
    std::pair<int, int> markedPos = std::make_pair(inpY, inpX);

    for (int ii = 0; ii < entityFleet.size(); ++ii)
    {
        for (int i = 0; i < entityFleet[ii].length(); ++i)
        {
            if (entityFleet[ii].getPosition(i) == markedPos && !entityFleet[ii].isHit(i))
            {
                entityFleet[ii].gotHit(i);

                return true;
            }
        }
    }

    return false;
}

int hitCount(std::vector<Ship> entityFleet)
{
    int count = 0;
    for (auto ship : entityFleet)
    {
        for (int i = 0; i < ship.length(); ++i)
        {
            if (ship.isHit(i))
            {
                count++;
            }
        }
    }
    return count;
}

bool gameRezult(int health1, int health2)
{
    if (health1 == 0 || health2 == 0)
    {
        if (health2 == 0)
        {
            std::cout << "\nYOU LOSE\n";
        }
        else
        {
            std::cout << "\nYOU WON\n";
        }
        return true;
    }
    return false;
}

void enemyShotCoor(Map entity, int &genY, int &genX, bool isLastShotHit)
{
    int sizeY = entity.getMapY(),
        sizeX = entity.getMapX();

    static std::pair<int, int> hitCoor;
    static std::vector<std::pair<int, int>> coorPool;

    if (coorPool.empty())
    {
        for (int i = 0; i < sizeY; ++i)
        {
            for (int j = 0; j < sizeX; ++j)
            {
                coorPool.push_back(std::make_pair(i, j));
            }
        }
    }

    int index = rand() % coorPool.size();
    std::pair<int, int> temp = coorPool[index];
    genY = temp.first;
    genX = temp.second;

    coorPool.erase(coorPool.begin() + index);

    return;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    system("chcp 65001");
    clearLines(1);

    // Config file data variable
    std::string configFileName = "config.INI";
    mINI::INIStructure ini;

    // fail-safe for config file
    if (isFileInDirectory(configFileName))
    {
        mINI::INIFile file(configFileName);
        file.read(ini);
    }
    else
    {
        std::cout << "Config file was not found\n";
        return 0;
    }
    //----

    // Start Screen

    int keyPress;
    bool closeMainWin = false;
    std::cout << "\x1b[31m ___       _   _   _     ___ _    _\n"
              << "| _ ) __ _| |_| |_| |___/ __| |_ (_)_ __\n"
              << "| _ \\/ _` |  _|  _| / -_)__ \\ ' \\| | '_ \\ \n"
              << "|___/\\__,_|\\__|\\__|_\\___|___/_||_|_| .__/\n"
              << "                                   |_|   \n\n"
              << "\x1b[0mPress enter to start\n";
    while (true)
    {
        switch ((keyPress = _getch()))
        {
        case KEY_ENTER:
            closeMainWin = true;
            break;
        default:
            break;
        }
        if (closeMainWin)
        {
            clearLines(1);
            break;
        }
    }

    std::vector<Ship> playerFleet;
    std::vector<Ship> enemyFleet;

    // Populates fleet Vectors
    for (int i = 0; i < stoi(ini["SHIP_INFO"]["ShipCount"]); ++i)
    {
        Ship temp(ini, i);
        playerFleet.push_back(temp);
        enemyFleet.push_back(temp);
    }

    Map enemy(ini, false, "Enemy");
    Map player(ini, false, "Player");

    std::vector<int> toBigShips;

    enemy.setVisibility(DEBUG);
    player.setVisibility(true);

    // Placing whole fleet on the map
    for (int i = 0; i < enemyFleet.size(); ++i)
    {
        if (placeShipRandom(enemy, enemyFleet[i]))
        {
            if (DEBUG)
            {
                std::cout << "Ship " << enemyFleet[i].getName() << " is placed. " << enemyFleet[i].length() << "\n";
                std::cout << enemyFleet[i].getPosition(0).first << " " << enemyFleet[i].getPosition(0).second << " " << enemyFleet[i].isVertical() << "\n";
                Sleep(SLEEP);
                clearLines(2);
            }
        }
        else
        {
            toBigShips.push_back(i);
            if (DEBUG)
            {
                std::cout << "Ship " << enemyFleet[i].getName() << " cannot be placed. " << enemyFleet[i].length() << "\n";
                Sleep(SLEEP);
                clearLines(1);
            }
        }
    }
    //----
    // Checks if there was any ship that was not able to be placed
    if (DEBUG)
    {
        if (toBigShips.empty())
        {
            std::cout << "Every ship was able to be placed on the map\n";
            Sleep(SLEEP);
            clearLines(1);
        }
        else
        {
            std::cout << "The map is to small to put every ship\n";
            Sleep(SLEEP);
            clearLines(1);
        }
    }
    //----------------------
    enemy.update();
    player.update();

    static int inpY = 0, inpX = 0;
    static bool inpIsVertical = 0;
    bool isClose = false, placed = false;

    std::string display = enemy.show() + "\n" + player.show();
    std::cout << display;
    std::cout << inpY << " " << inpX << " " << inpIsVertical << "\n";

    // Player places ships
    for (int i = 0; i < playerFleet.size() - toBigShips.size(); ++i)
    {
        placed = false;
        isClose = false;

        while (true)
        {
            //!----------------
            int keyPress;

            switch ((keyPress = _getch()))
            {
            case KEY_UP:
                if (inpY - 1 >= 0)
                {
                    inpY--;
                }
                break;
            case KEY_DOWN:
                if (inpIsVertical && inpY + playerFleet[i].length() < player.getMapY())
                {
                    inpY++;
                }
                if (!inpIsVertical && inpY + 1 < player.getMapY())
                {
                    inpY++;
                }
                break;
            case KEY_LEFT:
                if (inpX - 1 >= 0)
                {
                    inpX--;
                }
                break;
            case KEY_RIGHT:
                if (inpIsVertical && inpX + 1 < player.getMapX())
                {
                    inpX++;
                }
                if (!inpIsVertical && inpX + playerFleet[i].length() < player.getMapX())
                {
                    inpX++;
                }
                break;

            case KEY_r:
            case KEY_R:
                if (inpIsVertical)
                {
                    if (inpX + playerFleet[i].length() - 1 < player.getMapX())
                    {
                        inpIsVertical = false;
                    }
                }
                else
                {
                    if (inpY + playerFleet[i].length() - 1 < player.getMapY())
                    {
                        inpIsVertical = true;
                    }
                }
                break;
            case KEY_ENTER:
                placed = true;
                break;
            case KEY_ESCAPE:
                isClose = true;
                break;
            default:
                break;
            }
            //!----------------

            if (isClose)
            {
                // if is closed ship is placed random . . . , maybe
                placeShipRandom(player, playerFleet[i]);
            }
            /// place ship
            if (placed && isGeneratedCoordinatesValid(player, playerFleet[i], inpY, inpX, inpIsVertical))
            {
                playerFleet[i].placeShipAt(inpY, inpX, inpIsVertical); // y, x, isVertical
                for (int j = 0; j < playerFleet[i].length(); ++j)
                {
                    // Draws ship on the map
                    std::pair<int, int> tempCoor = playerFleet[i].getPosition(j);
                    player.setCell(tempCoor.first, tempCoor.second, playerFleet[i].length());
                    player.setCell(tempCoor.first, tempCoor.second, playerFleet[i].getLayout(j));
                    //----
                }
            }
            else
            {
                placed = false;
            }
            clearLines(2 * player.getMapY() + 2);
            player.update();
            if (!isClose && !placed)
            {
                player.select(inpY, inpX, inpIsVertical, playerFleet[i].length(), "\x1b[102m");
            }

            display = enemy.show() + "\n" + player.show();

            std::cout << display;
            std::cout << inpY << " " << inpX << " " << inpIsVertical << " | " << playerFleet[i].getName() << " " << playerFleet[i].length() << "\n";
            if (placed || isClose)
            {
                break;
            }
        }
    }
    //----

    player.update();
    inpY = 0;
    inpX = 0;
    int genY, genX;
    bool hitPlayer = false;

    int playerHealth = 0;
    int enemyHealth = 0;

    for (int i = 0; i < enemyFleet.size(); i++)
    {
        enemyHealth += enemyFleet[i].length();
    }
    playerHealth = enemyHealth;

    // gameplay
    while (true)
    {
        while (true)
        {
            placed = false;
            isClose = false;

            //!----------------
            int keyPress;

            switch ((keyPress = _getch()))
            {
            case KEY_UP:
                if (inpY - 1 >= 0)
                {
                    inpY--;
                }
                break;
            case KEY_DOWN:
                if (inpY + 1 < enemy.getMapY())
                {
                    inpY++;
                }
                break;
            case KEY_LEFT:
                if (inpX - 1 >= 0)
                {
                    inpX--;
                }
                break;
            case KEY_RIGHT:
                if (inpX + 1 < enemy.getMapX())
                {
                    inpX++;
                }
                break;
            case KEY_ENTER:
                if (!enemy.isCellHit(inpY, inpX))
                {
                    placed = true;
                }
                break;
            case KEY_ESCAPE:
                isClose = true;
                break;
            default:
                break;
            }
            //!----------------
            if (isClose)
            {
                return 0;
            }
            if (placed)
            {
                enemy.setCell(inpY, inpX, true);
                shotRegister(enemyFleet, inpY, inpX);
            }
            clearLines(2 * player.getMapY() + 2);
            enemy.update();
            enemy.select(inpY, inpX, 0, 1, "\x1b[41m");

            display = enemy.show() + "\n" + player.show();
            std::cout << display;
            std::cout << inpY << " " << inpX << "\n";
            if (placed)
            {
                break;
            }
        }

        if (gameRezult(enemyHealth - hitCount(enemyFleet), playerHealth - hitCount(playerFleet)))
        {
            break;
        }
        /// enemy shots
        enemyShotCoor(enemy, genY, genX, hitPlayer);
        // checks if hit
        player.setCell(genY, genX, true);
        hitPlayer = shotRegister(playerFleet, genY, genX);

        clearLines(2 * enemy.getMapY() + 2);
        player.update();

        display = enemy.show() + "\n" + player.show();
        std::cout << display;
        std::cout << inpY << " " << inpX << "\n";

        if (gameRezult(enemyHealth - hitCount(enemyFleet), playerHealth - hitCount(playerFleet)))
        {
            break;
        }
    }
    return 0;
}
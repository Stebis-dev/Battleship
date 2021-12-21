#include <iostream>
#include <iomanip>
#include <random>
#include <conio.h>
#include <windows.h>

// cin.get(); // wait

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

using namespace std;

struct map
{
    int shipMap[11][11] = {0};
    int hitMarkerMap[11][11] = {0};
    int forDisplay[11][11] = {0};
    int lives = 17;
    char finalMap[11][11];
    int lastX = 0;
    int lastY = 0;
};
struct selection
{
    int x;
    int y;
    int size[10][10] = {0};
    bool AIUse;
    bool PLayerUse;
};

bool menu(int &menuState);

void gridDisplay(map player, map AI, selection shoot);
void gridDisplay(map player, map AI);
void placingShip(map &player, map &AI, int shipType);

void AIshipPlacing(map &AI);
void AIShips(map &AI, int shipType);

bool playerShoot(map &player, map &AI);

bool AIShoot(map &player, map AI);

void title();
void mapElementDisplay(int mainColor, char element, int defaultColor);
void enemyHitMarkerUpdate(map &AI);
void playerHitMarkerUpdate(map &player);
void drawingShips(map &object);

int main()
{
    map player, AI;
    int menuState;

    //-------------Menu-------------
    if (menu(menuState))
    {
        return 0;
    }
    //-------------    -------------

    //-------------AI ship placing-------------
    AIshipPlacing(AI);
    //-------------               -------------

    //-------------Placing Ships-------------
    //          5 - Aircraft carrier
    //          4 - Battleship
    //          3 - Destroyer (quantity of 2)
    //          2 - Patrol
    playerHitMarkerUpdate(player);
    drawingShips(player);
    placingShip(player, AI, 2);
    placingShip(player, AI, 3);
    placingShip(player, AI, 3);
    placingShip(player, AI, 4);
    placingShip(player, AI, 5);

    //-------------            -------------

    while (AI.lives > 0 || player.lives > 0)
    {
        // system("cls");
        // gridDisplay(player, AI);
        while (true)
        {
            if (!playerShoot(player, AI))
            {
                break;
            }
        }
        while (true)
        {
            if (!AIShoot(player, AI))
            {
                break;
            }
        }
        if (AI.lives == 0 || player.lives == 0)
        {
            cout << "END";
            break;
        }
    }
    return 0;
}

bool menu(int &menuState)
{
    menuState = 0;
    int marked = -1;
    string menuText[2] = {"Play Battleship", "Exit"};
    int keyPress, menuTextSize = (sizeof(menuText) / sizeof(*menuText));

    while (true)
    {
        system("cls");

        //-----------BattleShip title-------------
        title();
        //----------------------------------------

        // Menu display
        for (size_t i = 0; i < menuTextSize; ++i)
        {
            cout << "\n\t\t";
            if (marked == i)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
                cout << menuText[i];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else
            {
                cout << menuText[i];
            }
        }
        cout << "\n\n\n";

        // Menu selection
        switch ((keyPress = _getch()))
        {
        case KEY_UP:
            if (marked == -1)
            {
                marked = 0;
            }
            else if (marked > 0)
            {
                marked--;
            }
            break;
        case KEY_DOWN:
            if (marked == -1)
            {
                marked = 0;
            }
            else if (marked < menuTextSize - 1)
            {
                marked++;
            }
            break;
        case KEY_ENTER:
            if (marked == -1)
            {
                break;
            }
            else
            {
                switch (marked)
                {
                case 0:
                    return false;
                case 1:
                    return true;
                }
            }
        default:
            break;
        }
    }
}

void gridDisplay(map player, map AI, selection shoot)
{
    // system("cls");

    char TopRow[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    char background = (char)254;
    int red = 12, blue = 9, white = 15, selected = 236, green = 10;
    //-----------BattleShip title-------------
    title();
    //----------------------------------------

    //-----------------AI map-----------------
    enemyHitMarkerUpdate(AI);

    cout << "\n\t\t   ";
    for (int i = 0; i < 10; i++)
    {
        cout << TopRow[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < 10; i++)
    {
        cout << "\t\t" << setw(2) << i + 1 << " ";
        for (int j = 0; j < 10; j++)
        {
            // color
            if (AI.shipMap[i][j] == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blue);
            }
            else if (AI.hitMarkerMap[i][j] == 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), red);
            }
            if (AI.hitMarkerMap[i][j] == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blue);
            }
            // shooting selection always last, to overwrite the other colors
            if (shoot.AIUse && !shoot.PLayerUse && shoot.x == j && shoot.y == i)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selected);
            }
            // display
            if (DEBUG || AI.hitMarkerMap[i][j] != 0)
            {
                cout << AI.finalMap[i][j];
            }
            else
            {
                cout << background;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
            cout << " ";
        }
        cout << "\n";
    }
    //-----------------      -----------------
    cout << "\t\t-----------------------\n";
    playerHitMarkerUpdate(player);
    //-----------------Player map-----------------
    for (int i = 0; i < 10; i++)
    {
        cout << "\t\t" << setw(2) << i + 1 << " ";
        for (int j = 0; j < 10; j++)
        {
            // color
            if (player.shipMap[i][j] == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blue);
            }
            else if (player.hitMarkerMap[i][j] == 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), red);
            }
            else if (player.shipMap[i][j] > 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), green);
            }
            else if (player.hitMarkerMap[i][j] == 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blue);
            }
            if (shoot.PLayerUse && shoot.size[i][j] > 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selected);
            }
            // displa
            cout << player.finalMap[i][j];

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
            cout << " ";
        }
        cout << "\n";
    }
    cout << "\t\t   ";
    for (int i = 0; i < 10; i++)
    {
        cout << TopRow[i] << " ";
    }
    cout << "\n";
    //-----------------          -----------------

    return;
}
void gridDisplay(map player, map AI)
{
    // system("cls");

    char TopRow[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    char background = (char)254;
    int red = 12, blue = 9, white = 15, selected = 240;
    //-----------BattleShip title-------------
    title();
    //----------------------------------------

    //-----------------AI map-----------------
    enemyHitMarkerUpdate(AI);

    cout << "\n\t\t   ";
    for (int i = 0; i < 10; i++)
    {
        cout << TopRow[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < 10; i++)
    {
        cout << "\t\t" << setw(2) << i + 1 << " ";
        for (int j = 0; j < 10; j++)
        {
            // color
            if (AI.shipMap[i][j] == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blue);
            }
            else if (AI.hitMarkerMap[i][j] == 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), red);
            }
            // display
            if (DEBUG && AI.shipMap[i][j] > 1)
            {
                cout << AI.finalMap[i][j];
            }
            else
            {
                cout << AI.finalMap[i][j];
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
            cout << " ";
        }
        cout << "\n";
    }
    //-----------------      -----------------
    cout << "\t\t-----------------------\n";
    //-----------------Player map-----------------
    for (int i = 0; i < 10; i++)
    {
        cout << "\t\t" << setw(2) << i + 1 << " ";
        for (int j = 0; j < 10; j++)
        {
            if (player.hitMarkerMap[i][j] == -1)
            {
                cout << '*' << " ";
            }
            else if (player.hitMarkerMap[i][j] == 1)
            {
                cout << '+' << " ";
            }
            else
            {
                if (player.shipMap[i][j] == 0)
                {
                    mapElementDisplay(9, background, 15);
                }
                else
                {
                    cout << player.shipMap[i][j] << " ";
                }
            }
        }
        cout << "\n";
    }
    cout << "\t\t   ";
    for (int i = 0; i < 10; i++)
    {
        cout << TopRow[i] << " ";
    }
    cout << "\n";
    //-----------------          -----------------

    return;
}
void placingShip(map &player, map &AI, int shipType)
{
    if (shipType < 2 || shipType > 5)
    {
        cout << "_ERROR_ wrong shipType!! <" << shipType << "> this ship type does not exists \n";
        return;
    }
    int quantity = 0;
    int keyPress;
    int direction = 0; // 0 or 1 --> 0 horizontally, 1 vertically
    bool loopState = true;
    selection forPlacing;
    //----------------------
    // ships menu
    // 5 - Aircraft carrier
    // 4 - Battleship
    // 3 - Destroyer (quantity of 2)
    // 2 - Patrol

    forPlacing.x = player.lastX;
    forPlacing.y = player.lastY;
    forPlacing.PLayerUse = true;
    forPlacing.AIUse = false;

    string shipName[6] = {"_",
                          "_",
                          "Patrol",
                          "Destroyer",
                          "Battleship",
                          "Aircraft carrier"};

    while (loopState)
    {
        player.lastX = forPlacing.x;
        player.lastY = forPlacing.y;

        system("cls");
        gridDisplay(player, AI, forPlacing);

        cout << "\n\tPlace " << shipName[shipType];

        switch ((keyPress = _getch()))
        {
        case KEY_UP:
            if (forPlacing.y - 1 >= 0)
                forPlacing.y--;
            break;
        case KEY_DOWN:
            if (direction && forPlacing.y + 1 <= 10 - shipType)
            {
                forPlacing.y++;
            }
            else if (forPlacing.y + 1 <= 9)
            {
                forPlacing.y++;
            }
            break;
        case KEY_LEFT:
            if (forPlacing.x - 1 >= 0)
                forPlacing.x--;
            break;
        case KEY_RIGHT:
            if (direction && forPlacing.x + 1 <= 9)
            {
                forPlacing.x++;
            }
            else if (forPlacing.x + 1 + shipType <= 10)
            {
                forPlacing.x++;
            }
            break;

        case KEY_R:
            if (direction)
            {
                direction = 0;
            }
            else
            {
                direction = 1;
            }
            break;
        case KEY_r:
            if (direction)
            {
                direction = 0;
            }
            else
            {
                direction = 1;
            }
            break;
        case KEY_ENTER:
            if (direction)
            {
                if (forPlacing.y >= 0 && (forPlacing.y + shipType) <= 10)
                {
                    quantity = 0;
                    for (int i = 0; i < shipType; i++)
                    {
                        if (player.shipMap[forPlacing.y + i][forPlacing.x] == 0)
                        {
                            quantity++;
                        }
                    }
                }
            }
            else
            {
                if (forPlacing.x >= 0 && (forPlacing.x + shipType) <= 10)
                {
                    for (int i = 0; i < shipType; i++)
                    {
                        if (player.shipMap[forPlacing.y][forPlacing.x + i] == 0)
                        {
                            quantity++;
                        }
                    }
                }
            }
            if (quantity == shipType)
            {
                loopState = false;
            }
            break;
        default:
            break;
        }

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                forPlacing.size[i][j] = 0;
            }
        }
        for (int i = 0; i < shipType; i++)
        {
            if (direction)
            {
                forPlacing.size[forPlacing.y + i][forPlacing.x]++;
            }
            else
            {
                forPlacing.size[forPlacing.y][forPlacing.x + i]++;
            }
        }
    }

    if (direction)
    {
        for (int i = 0; i < shipType; i++)
        {
            player.shipMap[forPlacing.y + i][forPlacing.x] = shipType;
        }
    }
    else
    {
        for (int i = 0; i < shipType; i++)
        {
            player.shipMap[forPlacing.y][forPlacing.x + i] = shipType;
        }
    }
    drawingShips(player);

    system("cls");
    gridDisplay(player, AI);
    return;
}

void AIshipPlacing(map &AI)
{
    AIShips(AI, 2);
    AIShips(AI, 3);
    AIShips(AI, 3);
    AIShips(AI, 4);
    AIShips(AI, 5);

    drawingShips(AI);
    return;
}
void AIShips(map &AI, int shipType)
{
    random_device rd;  // non-deterministic generator
    mt19937 gen(rd()); // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 9);

    bool loopState = true;
    int x, y;
    int quantity = 0;
    while (loopState)
    {
        quantity = 0;
        x = dist(gen);
        y = dist(gen);

        if (dist(gen) % 2 == 0) // vertical
        {
            if (y >= 0 && y + shipType < 10)
            {
                for (int i = 0; i < shipType; i++)
                {
                    if (AI.shipMap[y + i][x] != 0)
                    {
                        break;
                    }
                    else
                    {
                        quantity++;
                    }
                }
            }
            if (quantity == shipType)
            {
                for (int i = 0; i < shipType; i++)
                {
                    AI.shipMap[y + i][x] = shipType;
                }
                loopState = false;
            }
        }
        else // horizontally
        {
            if (x >= 0 && x + shipType < 10)
            {
                for (int i = 0; i < shipType; i++)
                {
                    if (AI.shipMap[y][x + i] != 0)
                    {
                        break;
                    }
                    else
                    {
                        quantity++;
                    }
                }
            }
            if (quantity == shipType)
            {
                for (int i = 0; i < shipType; i++)
                {
                    AI.shipMap[y][x + i] = shipType;
                }
                loopState = false;
            }
        }
    }
}

bool playerShoot(map &player, map &AI)
{
    bool loopState = true;
    int keyPress;
    selection forShooting;

    forShooting.x = player.lastX;
    forShooting.y = player.lastY;
    forShooting.AIUse = true;
    forShooting.PLayerUse = false;

    while (loopState)
    {
        if (AI.lives == 0)
        {
            return false;
        }

        system("cls");
        gridDisplay(player, AI, forShooting);

        switch ((keyPress = _getch()))
        {
        case KEY_UP:
            if (forShooting.y - 1 >= 0)
                forShooting.y--;
            break;
        case KEY_DOWN:
            if (forShooting.y + 1 <= 9)
                forShooting.y++;
            break;
        case KEY_LEFT:
            if (forShooting.x - 1 >= 0)
                forShooting.x--;
            break;
        case KEY_RIGHT:
            if (forShooting.x + 1 <= 9)
                forShooting.x++;
            break;

        case KEY_ENTER:
            if ((forShooting.y >= 0 && forShooting.y < 10) && (forShooting.x >= 0 && forShooting.x < 10) &&
                AI.hitMarkerMap[forShooting.y][forShooting.x] == 0)
            {
                loopState = false;
            }
            break;
        default:
            break;
        }
    }
    player.lastX = forShooting.x;
    player.lastY = forShooting.y;

    if (AI.shipMap[forShooting.y][forShooting.x] != 0)
    {
        AI.hitMarkerMap[forShooting.y][forShooting.x] = 1;
        AI.lives--;
        return true;
    }
    else
    {
        AI.hitMarkerMap[forShooting.y][forShooting.x] = -1;
        return false;
    }
}
bool AIShoot(map &player, map AI)
{

    random_device rd;  // non-deterministic generator
    mt19937 gen(rd()); // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 9);

    bool loopState = true;
    int x, y;
    if (player.lives == 0)
    {
        return false;
    }
    while (loopState)
    {
        x = dist(gen);
        y = dist(gen);
        if (player.hitMarkerMap[y][x] == 0)
        {
            break;
        }
    }
    if (player.shipMap[y][x] != 0)
    {
        player.hitMarkerMap[y][x] = 1;
        player.lives--;
        return true;
    }
    else
    {
        player.hitMarkerMap[y][x] = -1;
        return false;
    }
}
void title()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << " ____            _     _     _                _       _\n"
         << "|  _ \\          | |   | |   | |              | |     (_)\n"
         << "| |_) |  __  _  | |_  | |_  | |   ___   ___  | |__    _   _ __ \n"
         << "|  _ <  /  _` | | __| | __| | |  / _ \\ / __| | '_ \\  | | | '_  \\ \n"
         << "| |_) | | (_| | | |_  | |_  | |  |__ / \\__ \\ | | | | | | | |_) | \n"
         << "|____ / \\__,_ | \\__ | \\__ | |_|  \\___| |___/ |_| |_| |_| | .__ / \n"
         << "                                                         | |\n"
         << "                                                         |_| \n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return;
}
void mapElementDisplay(int mainColor, char element, int defaultColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mainColor);
    cout << element << " ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
    return;
}
void enemyHitMarkerUpdate(map &AI)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (AI.hitMarkerMap[i][j] == -1)
            {
                AI.finalMap[i][j] = '*';
            }
            else if (AI.hitMarkerMap[i][j] == 1)
            {
                AI.finalMap[i][j] = '+';
            }
        }
    }

    return;
}
void playerHitMarkerUpdate(map &player)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (player.hitMarkerMap[i][j] == -1)
            {
                player.finalMap[i][j] = '*';
            }
            else if (player.hitMarkerMap[i][j] == 1)
            {
                player.finalMap[i][j] = '+';
            }
        }
    }
    return;
}
void drawingShips(map &object)
{

    int background = (char)254;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            object.forDisplay[i][j] = object.shipMap[i][j];
            object.finalMap[i][j] = background;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (object.forDisplay[i][j] != 0)
            {
                if (object.forDisplay[i][j + 1] == object.forDisplay[i][j] && j < 9)
                {
                    object.finalMap[i][j] = '<';
                    object.forDisplay[i][j] = 0;
                    for (int t = 1; t < object.shipMap[i][j] - 1; t++)
                    {
                        object.finalMap[i][j + t] = (char)254;
                        object.forDisplay[i][j + t] = 0;
                    }
                    object.finalMap[i][j + object.shipMap[i][j] - 1] = '>';
                    object.forDisplay[i][j + object.shipMap[i][j] - 1] = 0;
                    j += object.shipMap[i][j] - 1;
                }
            }
            if (object.forDisplay[i][j] != 0)
            {
                if (object.forDisplay[i + 1][j] == object.forDisplay[i][j] && i < 9)
                {
                    object.finalMap[i][j] = 'A';
                    object.forDisplay[i][j] = 0;
                    for (int t = 1; t < object.shipMap[i][j] - 1; t++)
                    {
                        object.finalMap[i + t][j] = (char)219;
                        object.forDisplay[i + t][j] = 0;
                    }
                    object.finalMap[i + object.shipMap[i][j] - 1][j] = 'V';
                    object.forDisplay[i + object.shipMap[i][j] - 1][j] = 0;
                }
            }
        }
    }
    return;
}
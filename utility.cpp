#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using namespace std;
using namespace nlohmann;

class Color
{
protected:
    int R, G, B;
    string hexa;

public:
    Color(string h) : hexa(h), R(0), G(0), B(0)
    {
        SetColors();
    }
    ~Color() {}
    // return ANSI color code string
    void SetColors()
    {
        hexa.erase(0, 1);
        int temp = stoi(hexa, 0, 16);
        R = temp >> 16;
        G = temp >> 8 & 0x00ff;
        B = temp & 0x0000ff;
    }
    string SetF()
    {
        return "\x1b[38;2;" + to_string(R) + ';' + to_string(G) + ';' + to_string(B) + 'm';
    }
    string SetB()
    {
        return "\x1b[48;2;" + to_string(R) + ';' + to_string(G) + ';' + to_string(B) + 'm';
    }
};

string RestorColor()
{
    return "\x1b[0m";
}
string SetB(int hexa)
{
    return "\x1b[48;2;" +
           to_string(hexa >> 16) + ';' + to_string(hexa >> 8 & 0x00ff) + ';' + to_string(hexa & 0x0000ff) + 'm';
}
string SetF(int hexa)
{
    return "\x1b[38;2;" +
           to_string(hexa >> 16) + ';' + to_string(hexa >> 8 & 0x00ff) + ';' + to_string(hexa & 0x0000ff) + 'm';
}

void GetConfigData(json &j)
{
    ifstream dataFromFile("config.json");

    if (dataFromFile.is_open())
    {
        dataFromFile >> j;
        dataFromFile.close();
    }
    else
    {
        // If config file were not found, the new one is created and set with default values
        ofstream dataToFile("config.json");
        j = {
            {"Map", {{"x", 10}, {"y", 10}}},
            {"Colors", {{"Enemy", {{"RGB", {255, 17, 0}}, {"HEX", "#ff1100"}}}, {"User", {{"RGB", {3, 252, 61}}, {"HEX", "#03fc3d"}}}}}

        };

        dataToFile << j;
        dataToFile.close();
    }
    return;
}
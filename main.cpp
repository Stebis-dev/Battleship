#include <iostream>
#include <fstream>
#include "json.hpp"
#include "utility.cpp"

#include <Windows.h>
#include <cstdlib>

using namespace std;

int main()
{
    json j;
    GetConfigData(j);
    Color uColor(j["Colors"]["User"]["HEX"]);

    cout << uColor.SetF() << SetB(0xf54278) << "<__>" << ResetColor();

    return 0;
}
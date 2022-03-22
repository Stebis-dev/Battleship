#include <iostream>
#include <fstream>
#include "json.hpp"
#include "utility.cpp"

using namespace std;

int main()
{
    json j;
    GetConfigData(j);

    Color uColor(j["Colors"]["User"]["HEX"]);

    cout << uColor.SetF() << SetB(0xf54278) << "<__>\n";

    for (int i = 0; i < 10; i++)
    {
        for (int i = 0; i < 10; i++)
        {
            cout << SetB(0x9ebae6) << SetF(0x9ebae6) << " .";
        }
        cout << '\n';
    }
    cout << RestorColor();
    return 0;
}
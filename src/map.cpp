#include <string>
#include "../include/map.hpp"

//! in separate header
bool toBoolean(const std::string str)
{
    if (str == "True" || str == "TRUE" || str == "true")
        return true;
    else
        return false;
}
//!-----------------

Map::Map(mINI::INIStructure ini, bool isFog, std::string ownerName)
{
    _y = std::stoi(ini["MAP"]["y"]);
    _x = std::stoi(ini["MAP"]["x"]);
    _visible = !isFog;
    _spaceBetweenShip = toBoolean(ini["MAP"]["Space"]);

    // Create a map
    _block.resize(_y, std::vector<Cell>(_x));
    for (int i = 0; i < _y; ++i)
    {
        for (int j = 0; j < _x; ++j)
        {
            _block[i][j].initialize();
        }
    }

    // Dynamic map populated with background symbol
    _visualBackground = ini["Map"]["Background"];
    _middleBlock = ini["Map"]["MiddleBlock"];

    for (int i = 0; i < _y; ++i)
    {
        for (int j = 0; j < _x; ++j)
        {
            _block[i][j].setDisplay(_visualBackground);
        }
    }
    _shipColor = "\x1b[" + ini[" MAP "][ownerName] + "m";
    _waterColor = "\x1b[" + ini["MAP"]["SeaColor"] + "m";
    _hitColor = "\x1b[" + ini["MAP"]["HitColor"] + "m";
    _defaultColor = "\x1b[0m";

    return;
}
Map::~Map()
{
}

std::string Map::show()
{
    std::string tempRender = "";

    for (int i = 0; i < _y; ++i)
    {
        for (int j = 0; j < _x; ++j)
        {
            // tempRender += _block[i][j].getRender() + " " + std::to_string(_block[i][j].isHit());
            tempRender += _block[i][j].getRender() + " ";
        }
        tempRender += "\n";
    }
    return tempRender;
}
void Map::update()
{
    for (int i = 0; i < _y; ++i)
    {
        for (int j = 0; j < _x; ++j)
        {
            if (_block[i][j].getValue() == 0)
            {
                _block[i][j].setRender(_waterColor + _block[i][j].getDisplay() + _defaultColor);
            }
            else
            {
                if (_visible)
                {
                    _block[i][j].setRender(_shipColor + _block[i][j].getDisplay() + _defaultColor);
                }
                else
                {
                    _block[i][j].setRender(_waterColor + _visualBackground + _defaultColor);
                }
            }
            if (_block[i][j].isHit())
            {
                _block[i][j].setRender(_hitColor + _block[i][j].getDisplay() + _defaultColor);
            }
        }
    }
    return;
}
void Map::select(int y, int x, bool IsVertical, int size, std::string color)
{
    std::string tempVisual = _visualBackground;
    int tempY = y, tempX = x;
    _block[tempY][tempX].setRender(color + tempVisual + _defaultColor);

    for (int i = 0; i < size - 1; ++i)
    {
        if (IsVertical)
        {
            tempY++;
        }
        else
        {
            tempX++;
        }

        if (_block[tempY][tempX].isHit() || _visible)
        {
            tempVisual = _block[tempY][tempX].getDisplay();
        }
        else
        {
            tempVisual = _visualBackground;
        }
        _block[tempY][tempX].setRender(color + tempVisual + _defaultColor);
    }
}
int Map::getMapY()
{
    return _y;
}
int Map::getMapX()
{
    return _x;
}
int Map::getCellValue(int i, int j)
{
    return _block[i][j].getValue();
}
bool Map::isCellHit(int i, int j)
{
    return _block[i][j].isHit();
}

void Map::setCell(int y, int x, int value)
{
    _block.at(y).at(x).setValue(value);
    return;
}
void Map::setCell(int y, int x, std::string value)
{
    _block.at(y).at(x).setDisplay(value);
    return;
}
void Map::setCell(int y, int x, bool value)
{
    _block[y][x].setHit(value);
    return;
}
void Map::setVisibility(bool value)
{
    _visible = value;
}

bool Map::isShipExpansionEnabled()
{
    return _spaceBetweenShip;
}
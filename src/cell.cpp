#include "../include/cell.hpp"

Cell::Cell()
{
    initialize();
}

Cell::~Cell()
{
}
void Cell::initialize()
{
    _hit = false;
    _shipType = 0;
    _display = "";
    _render = "";
}
void Cell::setDisplay(std::string sample)
{
    _display = sample;
    return;
}

std::string Cell::getDisplay()
{
    return _display;
}

void Cell::setRender(std::string sample)
{
    _render = sample;
    return;
}
std::string Cell::getRender()
{
    return _render;
}
int Cell::getValue()
{
    return _shipType;
}
void Cell::setValue(int sample)
{
    _shipType = sample;
    return;
}
void Cell::setHit(bool sample)
{
    _hit = sample;
    return;
}
bool Cell::isHit()
{
    return _hit;
}

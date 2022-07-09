// Maps cell class
#pragma once

#include <string>

class Cell
{
private:
    std::string _display;
    std::string _render;
    bool _hit;
    int _shipType; // value stored by ships length

public:
    //          Constructor and Destructor
    Cell();
    ~Cell();

    void initialize();

    void setValue(int sample);
    int getValue();

    void setDisplay(std::string sample);
    std::string getDisplay();

    void setRender(std::string sample);
    std::string getRender();

    void setHit(bool sample);
    bool isHit();
};

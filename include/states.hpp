#pragma once

class States
{
private:
    bool _placed;
    bool _destroyed;
    bool _vertical;

public:
    //          Constructor and destructor
    States();
    ~States();

    //          Setters
    void setPlaced(bool placed);
    void setDestroyed(bool destroyed);
    void setVertical(bool vertical);

    //          Getters
    bool isPlaced();
    bool isDestroyed();
    bool isVertical();
};

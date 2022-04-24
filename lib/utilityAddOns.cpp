#include "utilityAddOns.h"

bool toBoolean(const std::string str)
{
    if (str == "True" || str == "TRUE" || str == "true")
        return true;
    else
        return false;
}
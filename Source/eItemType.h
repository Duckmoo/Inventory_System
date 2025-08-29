#pragma once
#include <string>

enum eItemType 
{
    WEAPON = 1,
    ARMOR = 2,
    CONSUMABLE = 3,
    UTILITY = 4,
    UNKNOWN
    
};

// Converts an enum to a string.
std::string toString(eItemType itemType);

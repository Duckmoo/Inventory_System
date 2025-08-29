#include "eItemType.h"

std::string toString(eItemType _ItemType)
{
    switch (_ItemType) 
    {
        case WEAPON: return "Weapon";
        case ARMOR: return "Armor";
        case CONSUMABLE: return "Consumable";
        case UTILITY: return "Utility";
        default: return "Unknown";

    }
}

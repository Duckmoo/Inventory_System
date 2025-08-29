#pragma once
#include <string>
#include "cInventory.h"

class cInventoryIO
{
public:
    static bool LoadInventory(cInventory& _Inventory, const std::string& _FileName);

    static bool SaveInventory(cInventory& _Inventory, const std::string& _FileName);
};

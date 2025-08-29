#include "cInventoryIO.h"
#include "cInventory.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> // For std:;stof, std::stoi

//Helper function: Converts a string to eItemType.
eItemType StringToItemType(const std::string& _ItemType)
{
    if (_ItemType == "Weapon")
    {
        return WEAPON;
    }
    else if (_ItemType == "Armor")
    {
        return ARMOR;
    }
    else if (_ItemType == "Consumable")
    {
        return CONSUMABLE;
    }
    else if (_ItemType == "Utility")
    {
        return UTILITY;
    }
    else
    {
        return UNKNOWN;
    }
}

// Helper function: trim leading/trailing spaces
std::string Trim(const std::string& str)
{
    size_t start = 0;
    while (start < str.size() && str[start] == ' ') start++;

    size_t end = str.size();
    while (end > start && str[end - 1] == ' ') end--;

    return str.substr(start, end - start);
}

// Load Inventory from text file.
bool cInventoryIO::LoadInventory(cInventory& _Inventory, const std::string& _FileName)
{
    std::ifstream inFile(_FileName);
    if (!inFile)
    {
        std::cerr << "Error: Could not open file " << _FileName << "\n";
        return false;
    }

    bool bLoadedAny = false; // Flag to check if a file is loaded.
    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty()) continue; // Skip empty lines

        size_t firstDelim = line.find("//");
        size_t secondDelim = line.find("//", firstDelim + 2);
        size_t thirdDelim = line.find("//", secondDelim + 2);

        if (firstDelim == std::string::npos || secondDelim == std::string::npos || thirdDelim == std::string::npos)
        {
            std::cerr << "Warning: Line has incorrect format: " << line << "\n";
            continue;
        }

        // Extract tokens and trim spaces
        std::string sName = Trim(line.substr(0, firstDelim));
        std::string sType = Trim(line.substr(firstDelim + 2, secondDelim - (firstDelim + 2)));
        std::string sPrice = Trim(line.substr(secondDelim + 2, thirdDelim - (secondDelim + 2)));
        std::string sQuant = Trim(line.substr(thirdDelim + 2));

        // Convert to proper types safely
        float fPrice = 0.0f;
        int iQuant = 0;
        try
        {
            fPrice = std::stof(sPrice);
            iQuant = std::stoi(sQuant);
        }
        catch (const std::invalid_argument&)
        {
            std::cerr << "Warning: Could not convert price/quantity in line: " << line << "\n";
            continue; // skip invalid line
        }

        // Convert type string to enum
        eItemType type = StringToItemType(sType);

        // Add to inventory
        _Inventory.InsertItem(sName, type, fPrice, iQuant);

        bLoadedAny = true; // Successfully loaded a file.
    }

    inFile.close();
    return bLoadedAny;
}

bool cInventoryIO::SaveInventory(cInventory& _Inventory, const std::string& _FileName)
{
    std::ofstream outFile(_FileName);
    if (!outFile)
    {
        std::cerr << "Error: Could not open file " << _FileName << "\n";
        return false;
    }

    cItem* pCurrent = _Inventory.GetHead();

    if (pCurrent == nullptr)
    {
        std::cerr << "Warning: Inventory is empty, nothing will be saved.\n";
        outFile.close();
        return false;
    }

    while (pCurrent != nullptr)
    {
        outFile << pCurrent->GetName() << " // "
        << toString(pCurrent->GetItemType()) << " // "
        << pCurrent->GetPrice() << " // "
        << pCurrent->GetQuantity() << "\n";

        pCurrent = pCurrent->GetNext();
    }

    outFile.close();
    return true;
}

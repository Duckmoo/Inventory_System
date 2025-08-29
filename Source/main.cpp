#include <iostream>
#include <string>
#include "cInventory.h"
#include "cInventoryIO.h"

int main()
{
    cInventory _Inventory; // Main inventory object.
    int iChoice = 0; // Stores user's menu choice.

    do
    {
    // Display menu options to the user
        std::cout << "\n===== Inventory Menu =====\n";
        std::cout << "1. Load Inventory from File\n";
        std::cout << "2. Save Inventory to File\n";
        std::cout << "3. Add Item\n";
        std::cout << "4. Edit Item\n";
        std::cout << "5. Delete Item\n";
        std::cout << "6. Display Inventory\n";
        std::cout << "7. Sort Inventory\n";
        std::cout << "8. Exit\n";
        std::cout << "==========================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> iChoice))
        {
            std::cin.clear();

            char c;
            while (std::cin.get(c) && c != '\n')
            {
                continue;
            }
        }

        switch (iChoice)
        {
            case 1: // Load inventory from a file.
            {
                std::string sFileName;
                std::cout << "Enter filename to load: ";
                std::cin >> sFileName;

                bool bSuccess = cInventoryIO::LoadInventory(_Inventory, sFileName);

                if (bSuccess)
                {
                   std::cout << "Inventory loaded successfully from " << sFileName << "\n";
                }           
                else
                {
                    std::cerr << "Failed to load inventory from file: " << sFileName << "\n";
                }
                break;
            }
            case 2: // Save current inventory to file.
            {
                std::string sFileName;
                std::cout << "Enter filename to save: ";
                std::cin >> sFileName;

                if (cInventoryIO::SaveInventory(_Inventory, sFileName))
                {
                    std::cout << "Inventory saved successfully.\n";
                }
                else
                {
                    std::cout << "Failed to save inventory.\n";
                }
                break;
            }
            case 3: // Add item into inventory.
            {
                std::string name;
                std::cout << "Enter item name: ";
                std::getline(std::cin >> std::ws, name); // Supports multi-word names.

                int iTypeChoice;
                eItemType type;
                std::cout << "Choose item type (1. Weapon, 2. Armor. 3. Consumable. 4. Utility): ";
                std::cin >> iTypeChoice;

                switch (iTypeChoice)
                {
                    case 1: type = WEAPON; break;
                    case 2: type = ARMOR; break;
                    case 3: type = CONSUMABLE; break;
                    case 4: type = UTILITY; break;
                    default:
                    {
                        type = UNKNOWN;
                        std::cout << "Invalid type, set to UNKNOWN.\n";
                        break;
                    }
                }

                float fPrice;
                std::cout << "Enter item price: ";
                std::cin >> fPrice;

                int iQuant;
                std::cout << "Enter item quantity: ";
                std::cin >> iQuant;

                int iPosition = 0;
                std::cout << "Enter position to insert (-1 for tail): ";
                std::cin >> iPosition;

                _Inventory.InsertItem(name, type, fPrice, iQuant, iPosition);
                std::cout << "Item added successfully.\n";

                std::cout << "\nUpdate Inventory:\n";
                _Inventory.PrintList();
                break;
            }
            case 4: // Edit an existing item in inventory.
            {
                std::string sName;
                std::cout << "Enter the name of the item to edit: ";
                std::getline(std::cin >> std::ws, sName);
                _Inventory.EditItem(sName);

                std::cout << "\nUpdate Inventory:\n";
                _Inventory.PrintList();
                break;
            }
            case 5: // Delete an existing item in inventory.
            {
                std::string sName;
                std::cout << "Enter the name of the item to delete: ";
                std::getline(std::cin >> std::ws, sName);
                _Inventory.DeleteItem(sName);

                std::cout << "\nUpdated Inventory:\n";
                _Inventory.PrintList();
                break;
            }
            case 6: // Display all items in the inventory.
            {
                _Inventory.PrintList();
                break;
            }
            case 7: // Sort inventory.
            {
                if (_Inventory.GetHead() == nullptr)
                {
                    std::cout << "Inventory is empty. Nothing to sort.\n";
                    break;
                }

                int iSortChoice;
                std::cout << "Sort by: \n1. Name\n2. Item Type\n3. Price\n4. Quantity\n Enter choice: ";
                std::cin >> iSortChoice;

                if (iSortChoice == 1) // Name.
                {
                    int iOrderChoice;
                    std::cout << "Choose order:\n1. Ascending\n2. Descending: ";
                    std::cin >> iOrderChoice;
                    bool bAscending = (iOrderChoice == 1);

                    // Get the head and last node.
                    cItem* pLow = _Inventory.GetHead();

                    cItem* pHigh = pLow;
                    while (pHigh->GetNext() != nullptr)
                    {
                        pHigh = pHigh->GetNext();
                    }

                    // Call quicksort to the list.
                    _Inventory.SortByName(bAscending);

                    std::cout << "\nInventory sorted by name ("
                    << (bAscending ? "Ascending" : "Descending")
                    << "):\n";

                    _Inventory.PrintList();
                }
                else if (iSortChoice == 2)
                {
                    int iOrderChoice;
                    std::cout << "Choose order:\n1. Ascending\n2. Descending: ";
                    std::cin >> iOrderChoice;
                    bool bAscending = (iOrderChoice == 1);

                    // Get the head and last node.
                    cItem* pLow = _Inventory.GetHead();

                    cItem* pHigh = pLow;
                    while (pHigh->GetNext() != nullptr)
                    {
                        pHigh = pHigh->GetNext();
                    }

                    // Call quicksort to the list.
                    _Inventory.SortByItemType(bAscending);

                    std::cout << "\nInventory sorted by name ("
                    << (bAscending ? "Ascending" : "Descending")
                    << "):\n";

                    _Inventory.PrintList();
                }
                else if (iSortChoice == 3)
                {
                    int iOrderChoice;
                    std::cout << "Choose order:\n1. Ascending\n2. Descending: ";
                    std::cin >> iOrderChoice;
                    bool bAscending = (iOrderChoice == 1);

                    // Get the head and last node.
                    cItem* pLow = _Inventory.GetHead();

                    cItem* pHigh = pLow;
                    while (pHigh->GetNext() != nullptr)
                    {
                        pHigh = pHigh->GetNext();
                    }

                    // Call quicksort to the list.
                    _Inventory.SortByPrice(bAscending);

                    std::cout << "\nInventory sorted by name ("
                    << (bAscending ? "Ascending" : "Descending")
                    << "):\n";

                    _Inventory.PrintList();
                }
                else if (iSortChoice == 4)
                {
                    int iOrderChoice;
                    std::cout << "Choose order:\n1. Ascending\n2. Descending: ";
                    std::cin >> iOrderChoice;
                    bool bAscending = (iOrderChoice == 1);

                    // Get the head and last node.
                    cItem* pLow = _Inventory.GetHead();

                    cItem* pHigh = pLow;
                    while (pHigh->GetNext() != nullptr)
                    {
                        pHigh = pHigh->GetNext();
                    }

                    // Call quicksort to the list.
                    _Inventory.SortByQuantity(bAscending);

                    std::cout << "\nInventory sorted by name ("
                    << (bAscending ? "Ascending" : "Descending")
                    << "):\n";

                    _Inventory.PrintList();
                }
                else
                {
                    std::cout << "Invalid choice!";
                    break;
                }

                break;
            }
            case 8: // Exit program.
            {
                std::cout << "Exiting program.\n";
                break;
            }
            default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (iChoice != 8);
    

    return 0;
}

/*
Implementation of the cInventory header class.
*/

#include "cInventory.h"
#include <cassert>
#include <iostream>

cInventory::~cInventory()
{
    cItem* pDelete = pHead;

    while (pDelete != nullptr)
    {
        cItem* pNext = pDelete->GetNext();
        delete pDelete;
        pDelete = pNext;
    }

    pHead = nullptr;
    iInvSize = 0;
}

void cInventory::InsertItem(const std::string& _ItemName, eItemType _ItemType, float _Price, int _Quantity, int _Position)
{
    // Defensive checks.
    if (_ItemName.empty() || _Price < 0.0f || _Quantity < 0)
    {
        std::cerr << "Error: Invalid item parameters.\n";
        return;
    }

    if (_ItemType < WEAPON || _ItemType > UNKNOWN)
    {
        _ItemType = UNKNOWN;
    }

    cItem* pNew = new cItem(_ItemName, _ItemType, _Price, _Quantity);

    // Empty list -- new node becomes head.
    if (pHead == nullptr)
    {
        pNew->SetNext(nullptr);
        pNew->SetPrevious(nullptr);
        pHead = pNew;
        iInvSize++;
        std::cout << "Item '" << _ItemName << "' added as the first item.\n";
        return;
    }

    // Default position (-1) -- add to tail.
    if (_Position < 0 || _Position >= iInvSize)
    {
        cItem* pCurrent = pHead;
        while (pCurrent->GetNext() != nullptr)
        {
            pCurrent = pCurrent->GetNext();
        }

        pCurrent->SetNext(pNew);
        pNew->SetPrevious(pCurrent);
        pNew->SetNext(nullptr);

        iInvSize++;
        std::cout << "Item '" << _ItemName << "' added at the tail.\n";
        return;
    }

    // Insert at head.
    if (_Position == 0)
    {
        pNew->SetNext(pHead);
        pHead->SetPrevious(pNew);
        pNew->SetPrevious(nullptr);
        pHead = pNew;

        iInvSize++;
        std::cout << "Item '" << _ItemName << "' added at the head.\n";
        return;
    }

    // Insert in the middle.
    cItem* pCurrent = pHead;
    for (int i = 0; i < _Position - 1; i++)
    {
        pCurrent = pCurrent->GetNext();
    }

    cItem* pAfter = pCurrent->GetNext();

    pCurrent->SetNext(pNew);
    pNew->SetPrevious(pCurrent);

    pNew->SetNext(pAfter);
    pAfter->SetPrevious(pNew);

    iInvSize++;

    std::cout << "Item '" << _ItemName << "' inserted at position " << _Position << ".\n";
}

// // Searches the list based on the item's name.
void cInventory::DeleteItem(const std::string& _ItemName)
{
    if (pHead == nullptr) // Empty list.
    {
        std::cout << "Inventory is empty. Nothing to delete.\n";
        return;
    }

    cItem* pCurrent = pHead;

    // Search for the item by name.
    while (pCurrent != nullptr && pCurrent->GetName() != _ItemName)
    {
        pCurrent = pCurrent->GetNext();
    }

    if (pCurrent == nullptr)
    {
        std::cout << "Item '" << _ItemName << "' not found in inventory.\n";
        return;
    }

    // Update previous node if it exists.
    if (pCurrent->GetPrevious() != nullptr)
    {
        pCurrent->GetPrevious()->SetNext(pCurrent->GetNext());
    }
    else // Deleting head.
    {
        pHead = pCurrent->GetNext();
    }

    // Update next node if it exists.
    if (pCurrent->GetNext() != nullptr)
    {
        pCurrent->GetNext()->SetPrevious(pCurrent->GetPrevious());
    }

    delete pCurrent; // Free memory.
    iInvSize--;
}


void cInventory::EditItem(const std::string& _ItemName)
{
    if (pHead == nullptr)
    {
        std::cout << "Inventory is empty. Nothing to edit.\n";
        return;
    }

    // Find the item by name.
    cItem* pCurrent = pHead;
    while (pCurrent != nullptr && pCurrent->GetName() != _ItemName)
    {
        pCurrent = pCurrent->GetNext();
    }

    if (pCurrent == nullptr)
    {
        std::cout << "Item '" << _ItemName << "' not found in inventory.\n";
        return;
    }

    std::cout << "Editing item '" << _ItemName << "'. Leave input blank to keep current value.\n";

    std::string sNewName;
    std::cout << "Enter new name (current: " << pCurrent->GetName() << "): ";
    std::getline(std::cin >> std::ws, sNewName); // Handles multi-word input.
    if (!sNewName.empty())
    {
        pCurrent->SetName(sNewName);
    }

    int iTypeChoice;
    std::cout << "Enter new type (1. Weapon, 2. Armor, 3. Utility, 4. Consumable) (current: " << toString(pCurrent->GetItemType()) << "): ";
    std::cin >> iTypeChoice;
    if (iTypeChoice >= 1 && iTypeChoice <= 4)
    {
        pCurrent->SetItemType(static_cast<eItemType>(iTypeChoice));
    }

    float fNewPrice;
    std::cout << "Enter new price (current: " << pCurrent->GetPrice() << "): ";
    std::cin >> fNewPrice;
    if (fNewPrice >= 0.0f)
    {
        pCurrent->SetPrice(fNewPrice);
    }

    int iNewQuantity;
    std::cout << "Enter new price (current: " << pCurrent->GetQuantity() << "): ";
    std::cin >> iNewQuantity;
    if (iNewQuantity >= 0)
    {
        pCurrent->SetQuantity(iNewQuantity);
    }

    std::cout << "Item updated successfully.\n";
}

void cInventory::PrintList()
{
    // If the list is empty.
    if (pHead == nullptr)
    {
        std::cout << "Current Inventory is empty.";
        return; // Nothing to print.
    }
    
    std::cout << "\n=== Inventory List ===\n";
    cItem* pCurrent = pHead;

    int iIndex = 1;

    while (pCurrent != nullptr)
    {
        std::cout << iIndex++ << ". "
        << "Name: " << pCurrent->GetName() << " | "
        << "Type: " << toString(pCurrent->GetItemType()) << " | "
        << "Price: $" << pCurrent->GetPrice() << " | "
        << "Quantity: " << pCurrent->GetQuantity()
        << "\n";

        pCurrent = pCurrent->GetNext(); // Move to the next item in the inventory.
    }

    std::cout << "======================\n";
    
}

cItem* cInventory::GetTail(cItem* pCurr)
{
    while (pCurr != nullptr && pCurr->GetNext() != nullptr)
    {
        pCurr = pCurr->GetNext();
    }

    return pCurr;
}

// Swap function.
void cInventory::SwapItemData(cItem* pA, cItem* pB)
{
    if (pA == nullptr || pB == nullptr) return;

    // Temporary storage of pA data.
    std::string sTempName = pA->GetName();
    eItemType eTempType = pA->GetItemType();
    float fTempPrice = pA->GetPrice();
    int iTempQuant = pA->GetQuantity();

    // Copy pB data into pA.
    pA->SetName(pB->GetName());
    pA->SetItemType(pB->GetItemType());
    pA->SetPrice(pB->GetPrice());
    pA->SetQuantity(pB->GetQuantity());

    // Copy pA original data into pB.
    pB->SetName(sTempName);
    pB->SetItemType(eTempType);
    pB->SetPrice(fTempPrice);
    pB->SetQuantity(iTempQuant);
}

// Partition function.
cItem* cInventory::PartitionByName(cItem* pLow, cItem* pHigh, bool bAscending)
{
    // Choose the pivot variable.
    std::string sPivot = pHigh->GetName(); // Pivot variable set to last item in list.
    cItem* pI = pLow->GetPrevious();

    for (cItem* j = pLow; j != pHigh; j = j->GetNext())
    {
        bool bCondition = bAscending ? (j->GetName() <= sPivot) : (j->GetName() >= sPivot);
        if (bCondition)
        {
            pI = (pI == nullptr) ? pLow : pI->GetNext();

            // Swap data.
            SwapItemData(pI, j);
        }
    }

    pI = (pI == nullptr) ? pLow : pI->GetNext();

    //Final swap with pivot.
    SwapItemData(pI, pHigh);

    return pI;
}

// Partition by ItemType.
cItem* cInventory::PartitionItemType(cItem* pLow, cItem* pHigh, bool bAscending)
{
    eItemType ePivot = pHigh->GetItemType();
    cItem* pI = pLow->GetPrevious();

    for (cItem* j = pLow; j != pHigh; j = j->GetNext())
    {
        bool bCondition = bAscending ? (j->GetItemType() <= ePivot) : (j->GetItemType() >= ePivot);
        if (bCondition)
        {
            pI = (pI == nullptr) ? pLow : pI->GetNext();
            SwapItemData(pI, j);

        }
    }

    pI = (pI == nullptr) ? pLow : pI->GetNext();
    SwapItemData(pI, pHigh);

    return pI;
}

// Partition by Price.
cItem* cInventory::PartitionPrice(cItem* pLow, cItem* pHigh, bool bAscending)
{
    float fPivot = pHigh->GetPrice();
    cItem* pI = pLow->GetPrevious();

    for (cItem* j = pLow; j != pHigh; j = j->GetNext())
    {
        bool bCondition = bAscending ? (j->GetPrice() <= fPivot) : (j->GetPrice() >= fPivot);
        if (bCondition)
        {
            pI = (pI == nullptr) ? pLow : pI->GetNext();
            SwapItemData(pI, j);
        }
    }

    pI = (pI == nullptr) ? pLow : pI->GetNext();
    SwapItemData(pI, pHigh);

    return pI;
}

// Partition by Quantity.
cItem* cInventory::PartitionQuantity(cItem* pLow, cItem* pHigh, bool bAscending)
{
    int iPivot = pHigh->GetQuantity();
    cItem* pI = pLow->GetPrevious();

    for (cItem* j = pLow; j != pHigh; j = j->GetNext())
    {
        bool bCondition = bAscending ? (j->GetQuantity() <= iPivot) : (j->GetQuantity() >= iPivot);
        if (bCondition)
        {
            pI = (pI == nullptr) ? pLow : pI->GetNext();
            SwapItemData(pI, j);
        }
    }

    pI = (pI == nullptr) ? pLow : pI->GetNext();
    SwapItemData(pI, pHigh);

    return pI;
}

// Quicksort recursion.
void cInventory::QuickSortByName(cItem* pLow, cItem* pHigh, bool bAscending)
{
    // Base cases: empty range, single element, or crossed range.
    if (pLow == nullptr || pHigh == nullptr) return;
    if (pLow == pHigh) return;
    if (pLow == pHigh->GetNext()) return;

    cItem* pPivot = PartitionByName(pLow, pHigh, bAscending);
    if (pPivot == nullptr) return; // Shouldn't happen if Partition is correct.
    
    // Recurse on left side.
    if (pPivot->GetPrevious() != nullptr)
    {
        QuickSortByName(pLow, pPivot->GetPrevious(), bAscending);
    }

    // Recurse on right side.
    if (pPivot->GetNext() != nullptr)
    {
        QuickSortByName(pPivot->GetNext(), pHigh, bAscending);
    }
}

void cInventory::QuickSortItemType(cItem* pLow, cItem* pHigh, bool bAscending)
{
    // Base cases: empty range, single element, or crossed range.
    if (pLow == nullptr || pHigh == nullptr) return;
    if (pLow == pHigh) return;
    if (pLow == pHigh->GetNext()) return;

    cItem* pPivot = PartitionItemType(pLow, pHigh, bAscending);
    if (pPivot == nullptr) return; // Shouldn't happen if Partition is correct.
    
    // Recurse on left side.
    if (pPivot->GetPrevious() != nullptr)
    {
        QuickSortItemType(pLow, pPivot->GetPrevious(), bAscending);
    }

    // Recurse on right side.
    if (pPivot->GetNext() != nullptr)
    {
        QuickSortItemType(pPivot->GetNext(), pHigh, bAscending);
    }
}

void cInventory::QuickSortPrice(cItem* pLow, cItem* pHigh, bool bAscending)
{
    // Base cases: empty range, single element, or crossed range.
    if (pLow == nullptr || pHigh == nullptr) return;
    if (pLow == pHigh) return;
    if (pLow == pHigh->GetNext()) return;

    cItem* pPivot = PartitionPrice(pLow, pHigh, bAscending);
    if (pPivot == nullptr) return; // Shouldn't happen if Partition is correct.
    
    // Recurse on left side.
    if (pPivot->GetPrevious() != nullptr)
    {
        QuickSortPrice(pLow, pPivot->GetPrevious(), bAscending);
    }

    // Recurse on right side.
    if (pPivot->GetNext() != nullptr)
    {
        QuickSortPrice(pPivot->GetNext(), pHigh, bAscending);
    }
}

void cInventory::QuickSortQuantity(cItem* pLow, cItem* pHigh, bool bAscending)
{
    // Base cases: empty range, single element, or crossed range.
    if (pLow == nullptr || pHigh == nullptr) return;
    if (pLow == pHigh) return;
    if (pLow == pHigh->GetNext()) return;

    cItem* pPivot = PartitionQuantity(pLow, pHigh, bAscending);
    if (pPivot == nullptr) return; // Shouldn't happen if Partition is correct.
    
    // Recurse on left side.
    if (pPivot->GetPrevious() != nullptr)
    {
        QuickSortQuantity(pLow, pPivot->GetPrevious(), bAscending);
    }

    // Recurse on right side.
    if (pPivot->GetNext() != nullptr)
    {
        QuickSortQuantity(pPivot->GetNext(), pHigh, bAscending);
    }
}


// Public wrapper.
void cInventory::SortByName(bool bAscending)
{
    if (pHead == nullptr) return; // Empty or inventory has 1 item.
    cItem* pHigh = pHead;
    while (pHigh->GetNext())
    {
        pHigh = pHigh->GetNext();
    }

    QuickSortByName(pHead, pHigh, bAscending);
}

void cInventory::SortByItemType(bool bAscending)
{
    if (pHead == nullptr) return; // Empty or inventory has 1 item.
    cItem* pHigh = pHead;
    while (pHigh->GetNext())
    {
        pHigh = pHigh->GetNext();
    }

    QuickSortItemType(pHead, pHigh, bAscending);
}

void cInventory::SortByPrice(bool bAscending)
{
    if (pHead == nullptr) return; // Empty or inventory has 1 item.
    cItem* pHigh = pHead;
    while (pHigh->GetNext())
    {
        pHigh = pHigh->GetNext();
    }

    QuickSortPrice(pHead, pHigh, bAscending);
}

void cInventory::SortByQuantity(bool bAscending)
{
    if (pHead == nullptr) return; // Empty or inventory has 1 item.
    cItem* pHigh = pHead;
    while (pHigh->GetNext())
    {
        pHigh = pHigh->GetNext();
    }

    QuickSortQuantity(pHead, pHigh, bAscending);
}

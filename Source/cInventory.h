#pragma once
#include "cItem.h"

class cInventory
{
protected:
    cItem* pHead;
    int iInvSize;

    // Helpers for Quicksort
    cItem* GetTail(cItem* pCurr); // Find last node in list.
    cItem* PartitionByName(cItem* pLow, cItem* pHigh, bool bAscending);
    cItem* PartitionItemType(cItem* pLow, cItem* pHigh, bool bAscending);
    cItem* PartitionPrice(cItem* pLow, cItem* pHigh, bool bAscending);
    cItem* PartitionQuantity(cItem* pLow, cItem* pHigh, bool bAscending);
    void QuickSortByName(cItem* pLow, cItem* pHigh, bool bAscending);
    void QuickSortItemType(cItem* pLow, cItem* pHigh, bool bAscending);
    void QuickSortPrice(cItem* pLow, cItem* pHigh, bool bAscending);
    void QuickSortQuantity(cItem* pLow, cItem* pHigh, bool bAscending);

    // Swap data between two nodes.
    void SwapItemData(cItem* pA, cItem* pB);

public:
    // Constructor.
    cInventory()
    {
        pHead = nullptr;
        iInvSize = 0;
    }

    // Destructor.
    ~cInventory();

    // Inserts an item at the given position (default = end of list).
    void InsertItem(const std::string& _ItemName, eItemType _ItemType, float _Price, int _Quantity, int _Position = -1);

    void DeleteItem(const std::string& _ItemName);

    void EditItem(const std::string& _ItemName);

    void PrintList();

    inline cItem* GetHead() const {return pHead;}
    inline int GetSize() const {return iInvSize;}

    // Public wrapper for sorting by name.
    void SortByName(bool bAscending);
    void SortByItemType(bool bAscending);
    void SortByPrice(bool bAscending);
    void SortByQuantity(bool bAscending);
};

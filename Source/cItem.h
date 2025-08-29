/*
This header class will function as the node system in the doubly linked list.
*/
#pragma once
#include "eItemType.h"

class cItem
{
protected:
    std::string sItemName;
    eItemType itemType;
    float fPrice;
    int iQuantity;
    cItem* pNext;
    cItem* pPrevious;

public:
    // Constructor for an cItem object.
    cItem (std::string _ItemName, eItemType _ItemType, float _Price, int _Quantity)
    {
        sItemName = _ItemName;
        itemType = _ItemType;
        fPrice = _Price;
        iQuantity = _Quantity;
        pNext = nullptr;
        pPrevious = nullptr;
    }

    // Deconstructor.
    ~cItem() {};

    // Getters.
    std::string GetName() const
    {
        return sItemName;
    }

    eItemType GetItemType() const
    {
        return itemType;
    }

    float GetPrice() const
    {
        return fPrice;
    }

    int GetQuantity() const
    {
        return iQuantity;
    }

    cItem* GetNext()
    {
        return pNext;
    }

    cItem* GetPrevious()
    {
        return pPrevious;
    }

    // Setters.
    void SetName (const std::string& _ItemName)
    {
        sItemName = _ItemName;
    }

    void SetItemType (eItemType _ItemType)
    {
        itemType = _ItemType;
    }

    void SetPrice (float _Price)
    {
        fPrice = _Price;
    }

    void SetQuantity (int _Quantity)
    {
        iQuantity = _Quantity;
    }

    void SetNext (cItem* _Next)
    {
        pNext = _Next;
    }

    void SetPrevious (cItem* _Previous)
    {
        pPrevious = _Previous;
    }
};

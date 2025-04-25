// IItem.h
#pragma once
#include "GameObject.h"

class IItem : public GameObject
{
public:
    virtual ~IItem()
    {
    }
    virtual HRESULT Init() = 0;
    virtual void Update() = 0;
    virtual void Render(HDC hdc) = 0;
    virtual void Use() = 0;
    virtual void SetPosition(int x, int y) = 0;

    virtual string GetName() const = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};
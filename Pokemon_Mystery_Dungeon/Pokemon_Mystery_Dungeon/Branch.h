#pragma once
#include <cstdlib>  // rand
#include <ctime>    // time

#include "IItem.h"
#include "Image.h"
class Image;
class Branch : public IItem
{
private:
    Image* image;

    int x;
    int y;
    int branchDamage;
    string name;

public:
    virtual HRESULT Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;
    virtual void Use() override;
    virtual void SetPosition(int newX, int newY) override;

    inline virtual string GetName() const override
    {
        return name;
    }
    inline virtual int GetX() const override
    {
        return x;
    }
    inline virtual int GetY() const override
    {
        return y;
    }
};

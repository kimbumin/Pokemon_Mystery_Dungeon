#pragma once
// clang-format off
#include "config.h"
// clang-format on

class Scene
{
public:
    virtual HRESULT Init() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
    virtual void Render(HDC hdc) = 0;

    Scene() {};
    virtual ~Scene()
    {
    }
};
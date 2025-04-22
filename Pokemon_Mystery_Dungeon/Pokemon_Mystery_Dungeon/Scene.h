#pragma once
#include "config.h"


class Scene {
public:
    virtual HRESULT Init() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
    virtual void Render(HDC hdc) = 0;

    Scene() {};
    virtual ~Scene() {}
};
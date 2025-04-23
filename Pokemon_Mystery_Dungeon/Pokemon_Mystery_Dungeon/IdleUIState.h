#pragma once
#include "UIState.h"

class IdleUIState : public UIState
{
public:
    IdleUIState() = default;
    ~IdleUIState() override = default;
    HRESULT Init() override
    {
        return S_OK;
    };
    void Release() override {};
    void Update() override {};
    void Render(HDC hdc) override {};
};

#pragma once
#include "UIState.h"

// 인벤토리 창
class InventoryUIState : public UIState
{
public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~InventoryUIState() override;
};

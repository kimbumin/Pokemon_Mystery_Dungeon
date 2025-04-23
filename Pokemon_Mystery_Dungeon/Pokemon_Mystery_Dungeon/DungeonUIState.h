#pragma once
#include "ImageGDIPlus.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIState.h"

class DungeonUIState : public UIState, public UIElement
{
private:
    UIElementImage* DungeonInfoBox = nullptr;
    UIElementImage* WaterType = nullptr;
    UIElementImage* FireType = nullptr;

    UIElementImage* Cursor = nullptr;

    UIElementText* IceTypeText = nullptr;
    UIElementText* MagmaTypeText = nullptr;
    UIElementText* ForestTypeText = nullptr;

    const int OffsetY[3] = {30, 60, 90};

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~DungeonUIState() override;
};

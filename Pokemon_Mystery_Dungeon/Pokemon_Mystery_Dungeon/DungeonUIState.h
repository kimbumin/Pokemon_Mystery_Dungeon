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

    UIElementText* WaterTypeText = nullptr;
    UIElementText* FireTypeText = nullptr;

    const int OffsetY[2] = {30, 110};

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~DungeonUIState() override;
};

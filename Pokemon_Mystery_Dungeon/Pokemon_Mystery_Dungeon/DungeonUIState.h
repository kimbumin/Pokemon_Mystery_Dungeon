#pragma once
#include "ImageGDIPlus.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIState.h"

class DungeonUIState : public UIState, public UIElement
{
private:
    UIElementImage* DungeonInfoBox = nullptr;

    UIElementImage* Cursor = nullptr;

    UIElementImage* IceType = nullptr;
    UIElementImage* MagmaType = nullptr;
    UIElementImage* ForestType = nullptr;

    UIElementText* IceTypeText = nullptr;
    UIElementText* MagmaTypeText = nullptr;
    UIElementText* ForestTypeText = nullptr;


    const int OffsetImageY[3] = {22, 72, 122};
    const int OffsetY[3] = {35, 90, 135};
    int YIndex = 0;

    bool isActive = false;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~DungeonUIState() override;

        bool GetIsActive()
    {
        return isActive;
    }
    void SetIsActive(bool isActive)
    {
        this->isActive = isActive;
    }

};

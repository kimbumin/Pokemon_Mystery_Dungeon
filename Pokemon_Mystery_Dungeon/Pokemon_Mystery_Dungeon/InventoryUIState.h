#pragma once
#include "UIState.h"
#include "UIElement.h"

// 인벤토리 창
class UIElementImage;
class UIElementText;
class InventoryUIState : public UIState, public UIElement
{
private:
    UIElementImage* InventoryBox = nullptr;
    UIElementImage* Cursor = nullptr;
    UIElementImage* FakeCursor = nullptr;

    UIElementText* ItemNameText = nullptr;
    UIElementText* ItemNameText2 = nullptr;

    UIElementImage* OtherInterfaceInfoBox = nullptr;

    UIElementText* SkillText = nullptr;
    UIElementText* ItemText = nullptr;
    UIElementText* SettingText = nullptr;


    const int InventoryBoxPosX = 75;
    const int InventoryBoxPosY = 75;
    const int ItemBoxPosX = 25;
    const int ItemBoxPosY = 25;
    const int CursorPosX = 75;
    const int CursorPosY[2] = {95, 140};
    int YIndex = 0;

    float fadeOutTime = 0.0f;
    float fadeInTime = 1.0f;


public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~InventoryUIState() override;
};

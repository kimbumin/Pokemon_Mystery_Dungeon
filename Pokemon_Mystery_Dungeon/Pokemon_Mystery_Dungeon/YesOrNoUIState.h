#pragma once
#include "UIElement.h"
#include "UIState.h"

class UIElementImage;
class UIElementText;
class YesOrNoUIState : public UIState, public UIElement
{
private:
    UIElementImage* YesOrNoBox = nullptr;
    UIElementText* YesText = nullptr;
    UIElementText* NoText = nullptr;
    UIElementImage* Cursor = nullptr;
    const int InfoBoxPosX = 40;  // 나중에 플레이어 위치에 맞춰서 바꿔야함
    const int InfoBoxPosYOffset[2] = {30, 60};

    float fadeOutTime = 0.0f;
    float fadeInTime = 1.0f;
    int YIndex = 0;
    const int CursorPosX = 20;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~YesOrNoUIState() override;
};

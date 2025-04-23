#pragma once
#include "UIState.h"
#include "UIElement.h"

class UIElementImage;
class UIElementText;
class DownStairUIState : public UIState, public UIElement
{
private:
    UIElementImage* DownStairBox = nullptr;
    UIElementImage* YesOrNoBox = nullptr;

    UIElementImage* Cursor = nullptr;

    UIElementText* IsDownText = nullptr;
    UIElementText* YesText = nullptr;
    UIElementText* NoText = nullptr;

    const int OffsetY[2] = {30, 60};

    int YIndex = 0;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~DownStairUIState() override;

};

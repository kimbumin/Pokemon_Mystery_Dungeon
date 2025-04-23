#pragma once
#include "ImageGDIPlus.h"
#include "UIElement.h"
#include "UIState.h"

class UIElementImage;
class UIElementText;
class InfoUIState : public UIState, public UIElement
{
private:
    UIElementImage* FirstInfoBox = nullptr;
    UIElementImage* SecondInfoBox = nullptr;
    UIElementImage* ThirdInfoBox = nullptr;
    UIElementImage* FourthInfoBox = nullptr;
    
    UIElementImage* CurrHpBar = nullptr;
    UIElementImage* MaxHpBar = nullptr;

    UIElementText* NameText = nullptr;
    UIElementText* LevelText = nullptr;
    UIElementText* HPText = nullptr;

    const int InfoBoxPosX = 500;

    int currentHP = 50;
    int maxHP = 100;

    float percent = (float)currentHP / maxHP;

    int barWidth;
    int barHeight;

    const int InfoBoxPosYOffset[4] = {0, 50, 100, 150};

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~InfoUIState() override;
    void SetInfoBoxText(int index, const wstring& text);
};

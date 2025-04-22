#pragma once
#include "ImageGDIPlus.h"
#include "UIElement.h"
#include "UIState.h"

class UIElementImage;
class UIElementText;
class DefaultUIState : public UIState, public UIElement
{
private:
    UIElementImage* OtherInterfaceInfoBox = nullptr;
    UIElementImage* PokemonInfoBox = nullptr;
    UIElementImage* MapInfoBox = nullptr;
    UIElementImage* Cursor = nullptr;

    //UIElementImage* OtherInterfaceInfoBoxOutline = nullptr;
    //UIElementImage* PokemonInfoBoxOutline = nullptr;
    //UIElementImage* MapInfoBoxOutline = nullptr;


    // other
    UIElementText* SkillText = nullptr;
    UIElementText* ItemText = nullptr;
    UIElementText* SettingText = nullptr;
    // map
    UIElementText* MapNameText = nullptr;
    // pokemon
    UIElementText* PokemonNameText = nullptr;
    UIElementText* PokemonLevelText = nullptr;
    UIElementText* PokemonHPText = nullptr;

    int fontPosX = 50;
    const int OffsetY[3] = {30, 70, 110};
    int YIndex = 0;

    float fadeOutTime = 0.0f;
    float fadeInTime = 1.0f;

public:
    HRESULT Init() override;

    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~DefaultUIState() override;
};

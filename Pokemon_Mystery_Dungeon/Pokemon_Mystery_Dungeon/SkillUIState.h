#pragma once
#include "ImageGDIPlus.h"
#include "UIElementImage.h"
#include "UIState.h"

// ��ų ���� UI
class UIElementText;
class SkillUIState : public UIState, public UIElement
{
public:
    struct SkillDisplayData
    {
        std::wstring SkillName;
        int currentCount;
        int maxCount;
    };
private:

    struct SkillUI
    {
        UIElementText* SkillName = nullptr;
        UIElementText* SkillCount = nullptr;
        UIElementText* SkillMaxCount = nullptr;
    };

    UIElementImage* SkillBox = nullptr;
    UIElementImage* SkillInfoBox = nullptr;
    UIElementImage* SkillAssistBox = nullptr;
    UIElementImage* UseInfoBox = nullptr;
    UIElementImage* Cursor = nullptr;

    UIElementText* PokemonName = nullptr;
    vector<SkillUI> SkillList;
    static const int SkillListMax = 4;

    UIElementImage* SubCursor = nullptr;
    UIElementText* SubText[4] = {};

    const int OffsetY[SkillListMax] = {70, 100, 130, 160};
    int YIndex = 0;
    float fadeOutTime = 0.0f;
    float fadeInTime = 1.0f;

    bool isSkillUseBox = false;
    int subCorsorIndex = 0;
    const int SubOffsetY[2] = {25, 55};
    const wstring subMenu[2] = {L"Use Skill",  L"Cancle Skill"};

    bool alreadyInitialized = false;
    int SelectedSkillIndex = -1;
    vector<SkillDisplayData> skillDisplayList;
    vector<SkillDisplayData> currentSkills;

    UIElementText* SkillNameText = nullptr;
    UIElementText* SkillTypeText = nullptr;
    UIElementText* SkillElementText = nullptr;
    UIElementText* SkillPowerText = nullptr;
    UIElementText* SkillAccuracyText = nullptr;
    UIElementText* SkillPPText = nullptr;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;

    void SetSkills(const vector<SkillDisplayData>& data);

    void UseSkill(int index);
    void UpdateSkillInfoText(int index);

    void SetElementTextColor(UIElementText* text, const string& element);

    void SetSelectedSkillIndex(int index)
    {
        SelectedSkillIndex = index;
    }
    int GetSelectedSkillIndex() const
    {
        return SelectedSkillIndex;
    }


    ~SkillUIState() override;
};

#pragma once
#include "ImageGDIPlus.h"
#include "UIElementImage.h"
#include "UIState.h"

// 스킬 정보 UI
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
    UIElementText* SubText[3] = {};

    const int OffsetY[SkillListMax] = {70, 100, 130, 160};
    int YIndex = 0;
    float fadeOutTime = 0.0f;
    float fadeInTime = 1.0f;

    bool isSkillUseBox = false;
    int subCorsorIndex = 0;
    const int SubOffsetY[3] = {25, 55, 85};
    const wstring subMenu[3] = {L"Use Skill", L"Info Skill", L"Cancle Skill"};

    bool alreadyInitialized = false;
    int SelectedSkillIndex = -1;
    vector<SkillDisplayData> skillDisplayList;
    vector<SkillDisplayData> currentSkills;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;

    void SetSkills(const vector<SkillDisplayData>& data);

    void UseSkill(int index);
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

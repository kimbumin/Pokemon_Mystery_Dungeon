#include "SkillUIState.h"

#include "ImageGDIPlusManager.h"
#include "Timer.h"
#include "UIManager.h"
#include "UIElementText.h"
#include "PlayerManager.h"
#include "ISkill.h" 
#include "PokemonPlayer.h"
#include "CommonFunction.h"

HRESULT SkillUIState::Init()
{
    //메인
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto SkillBoxImage = manager.AddImage(
        "SkillBox", L"Image/UIImage/SkillUIState/SkillBox.png");
    auto SkillAssistBoxImage = manager.AddImage(
        "SkillAssistBox", L"Image/UIImage/SkillUIState/SkillAssistBox.png");
    auto UseInfoBoxImage = manager.AddImage(
        "UseInfoBox", L"Image/UIImage/SkillUIState/UseInfoBox.png");
    auto CursorImage = manager.AddImage(
        "SkillInfoBoxCursor", L"Image/UIImage/SkillUIState/Cursor.png");

    // UI 엘리먼트 생성
    SkillBox = new UIElementImage();
    Cursor = new UIElementImage();
    UseInfoBox = new UIElementImage();
    SkillAssistBox = new UIElementImage();

    SkillBox->SetImage(SkillBoxImage);
    SkillAssistBox->SetImage(SkillAssistBoxImage);
    UseInfoBox->SetImage(UseInfoBoxImage);
    Cursor->SetImage(CursorImage);

    SkillBox->SetParent(this);
    SkillAssistBox->SetParent(this);
    UseInfoBox->SetParent(this);
    Cursor->SetParent(SkillBox);

    SkillBox->setAlpha(0.95f);
    UseInfoBox->setAlpha(0.95f);
    SkillAssistBox->setAlpha(0.95f);
    Cursor->SetLocalPos(25, OffsetY[YIndex]);
    SkillBox->SetLocalPos(25, 10);
    UseInfoBox->SetLocalPos(25, 250);
    SkillAssistBox->SetLocalPos(280, 48);

    for (int i = 0; i < SkillListMax; ++i)
    {
        SkillUI skillUI;
        skillUI.SkillName = new UIElementText();
        skillUI.SkillCount = new UIElementText();
        skillUI.SkillMaxCount = new UIElementText();

        int y = OffsetY[i];

        skillUI.SkillName->SetLocalPos(50, y);
        skillUI.SkillCount->SetLocalPos(200, y);
        skillUI.SkillMaxCount->SetLocalPos(230, y);

        skillUI.SkillName->SetFont(18);
        skillUI.SkillCount->SetFont(18);
        skillUI.SkillMaxCount->SetFont(18);

        skillUI.SkillName->SetParent(SkillBox);
        skillUI.SkillCount->SetParent(SkillBox);
        skillUI.SkillMaxCount->SetParent(SkillBox);

        SkillList.push_back(skillUI);
    }

    SkillNameText = new UIElementText();
    SkillTypeText = new UIElementText();
    SkillElementText = new UIElementText();
    SkillPowerText = new UIElementText();
    SkillAccuracyText = new UIElementText();
    SkillPPText = new UIElementText();

    UIElementText* skillTexts[] = {SkillNameText,     SkillTypeText,
                                   SkillElementText,  SkillPowerText,
                                   SkillAccuracyText, SkillPPText};

    const wchar_t* labels[] = {L"Name",  L"Type",     L"Element",
                               L"Power", L"Accuracy", L"PP"};

    for (int i = 0; i < 6; ++i)
    {
        skillTexts[i]->SetFont(17);
        skillTexts[i]->SetTextLine(4.0f);
        skillTexts[i]->SetParent(UseInfoBox);
    }

    SkillNameText->SetLocalPos(50, 30);
    SkillTypeText->SetLocalPos(250, 30);
    SkillElementText->SetLocalPos(50, 50);

    SkillPowerText->SetLocalPos(250, 50);
    SkillAccuracyText->SetLocalPos(50, 70);
    SkillPPText->SetLocalPos(250, 70);
    
    auto player = PlayerManager::GetInstance()->GetPlayer();
    for (int i = 0; i < 4; ++i)
    {
        std::shared_ptr<ISkill> skill = player->GetSkill(i);
        if (skill)
        {
            const SkillData& data = skill->GetSkillData();  

            SkillDisplayData display;
            display.SkillName =
                ToWString(data.name);
            display.currentCount = data.pp;
            display.maxCount = data.pp;

            skillDisplayList.push_back(display);
        }
    }

    // 서브
    SubCursor = new UIElementImage();
    SubCursor->SetImage(CursorImage);
    SubCursor->SetParent(SkillAssistBox);

    for (int i = 0; i < 2; ++i)
    {
        SubText[i] = new UIElementText();
        SubText[i]->SetFont(18);
        SubText[i]->SetText(subMenu[i]);
        SubText[i]->SetParent(SkillAssistBox);
        SubText[i]->SetLocalPos(50, SubOffsetY[i]);
    }

    if (!alreadyInitialized)
    {
        skillDisplayList.clear();

        auto player = PlayerManager::GetInstance()->GetPlayer();
        for (int i = 0; i < 4; ++i)
        {
            std::shared_ptr<ISkill> skill = player->GetSkill(i);
            if (skill)
            {
                const SkillData& data = skill->GetSkillData();

                SkillDisplayData display;
                display.SkillName = ToWString(data.name);
                display.currentCount = data.pp;
                display.maxCount = data.pp;

                skillDisplayList.push_back(display);
            }
        }

        currentSkills = skillDisplayList;  // 초기화 한 번만
        alreadyInitialized = true;
    }
    SetSkills(currentSkills);

    UpdateRealPos();

    return S_OK;
}

void SkillUIState::Release()
{
}

void SkillUIState::Update()
{
    UpdateSkillInfoText(YIndex);
    fadeOutTime += TimerManager::GetInstance()->GetDeltaTime();
    fadeInTime = (sinf(fadeOutTime * 6.0f) * 0.5f) + 0.5f;

    if (!isSkillUseBox)
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
        {
            SoundManager::GetInstance()->PlaySFX("button");
            YIndex = (YIndex + 1) % 4;
            Cursor->SetLocalPos(25, OffsetY[YIndex]);
            Cursor->UpdateRealPos();
            UpdateSkillInfoText(YIndex);
        }
        else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
        {
            SoundManager::GetInstance()->PlaySFX("button");
            YIndex = (YIndex - 1 + 4) % 4;
            Cursor->SetLocalPos(25, OffsetY[YIndex]);
            Cursor->UpdateRealPos();
            UpdateSkillInfoText(YIndex);
        }
    }
    else
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
        {
            SoundManager::GetInstance()->PlaySFX("button");
            subCorsorIndex = (subCorsorIndex + 1) % 2;
            SubCursor->SetLocalPos(25, SubOffsetY[subCorsorIndex]);
            SubCursor->UpdateRealPos();
        }
        else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
        {
            SoundManager::GetInstance()->PlaySFX("button");
            subCorsorIndex = (subCorsorIndex - 1 + 2) % 2;
            SubCursor->SetLocalPos(25, SubOffsetY[subCorsorIndex]);
            SubCursor->UpdateRealPos();
        }
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A))  // Z
    {
        if (!isSkillUseBox)
        {
            isSkillUseBox = true;
            subCorsorIndex = 0;
            SubCursor->SetLocalPos(25, SubOffsetY[subCorsorIndex]);
            SubCursor->UpdateRealPos();
        }
        else
        {
            switch (subCorsorIndex)
            {
                case 0:  // 스킬 사용
                    // 스킬 사용 로직 추가
                    UseSkill(YIndex);
                    isSkillUseBox = false;
                    SetSelectedSkillIndex(YIndex);
                    UIManager::GetInstance()->ChangeState("IdleUI");
                    break;
                case 1:  // 스킬 취소
                    isSkillUseBox = false;
                    break;
                default:
                    break;
            }
        }
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // X
    {
        if (isSkillUseBox)
        {
            isSkillUseBox = false;
        }
        else
        {
            UIManager::GetInstance()->ChangeState("defaultUI");
        }
    }
    if (!isSkillUseBox)
    {
        Cursor->setAlpha(fadeInTime);
    }
    else
    {
        SubCursor->setAlpha(fadeInTime);
    }
}

void SkillUIState::Render(HDC hdc)
{
    SkillBox->Render(hdc);
    UseInfoBox->Render(hdc);
    Cursor->Render(hdc);

    for (const auto& skill : SkillList)
    {
        skill.SkillName->Render(hdc);
        skill.SkillCount->Render(hdc);
        skill.SkillMaxCount->Render(hdc);
    }

    if (isSkillUseBox)
    {
        SkillAssistBox->Render(hdc);
    }
}

void SkillUIState::SetSkills(const vector<SkillDisplayData>& data)
{
    currentSkills = data;

    for (size_t i = 0; i < data.size() && i < SkillList.size(); ++i)
    {
        SkillList[i].SkillName->SetText(data[i].SkillName);

        wstring countText = to_wstring(data[i].currentCount);
        wstring maxCountText = L"/" + to_wstring(data[i].maxCount);

        SkillList[i].SkillCount->SetText(countText);
        SkillList[i].SkillMaxCount->SetText(maxCountText);
    }
}

void SkillUIState::UseSkill(int index)
{


    if (index < 0 || index >= currentSkills.size())
        return;

    if (currentSkills[index].currentCount > 0)
        currentSkills[index].currentCount--;

    SetSkills(currentSkills);


}

void SkillUIState::UpdateSkillInfoText(int index)
{
    auto* player = PlayerManager::GetInstance()->GetPlayer();
    if (!player)
        return;

    shared_ptr<ISkill> skill = player->GetSkill(index);
    if (!skill)
        return;

    const SkillData& data = skill->GetSkillData();

    SkillNameText->SetText(L"Name: " + ToWString(data.name));
    SkillTypeText->SetText(L"Type: " + ToWString(data.type));
    SkillElementText->SetText(L"Element: <" + ToWString(data.element) + L">");
    SkillPowerText->SetText(L"Power: " + to_wstring(data.power));
    SkillAccuracyText->SetText(L"Accuracy: " + to_wstring(data.accuracy));
    SkillPPText->SetText(L"PP: " + to_wstring(data.pp));

    SetElementTextColor(SkillElementText, data.element);
}

void SkillUIState::SetElementTextColor(UIElementText* text,
                                       const string& element)
{
    if (element == "Fire")
        text->SetHighlightColorRGB(255, 80, 0);
    else if (element == "Water")
        text->SetHighlightColorRGB(0, 120, 255);
    else if (element == "Grass")
        text->SetHighlightColorRGB(0, 200, 100);
    else if (element == "Electric")
        text->SetHighlightColorRGB(255, 215, 0);
    else if (element == "Ice")
        text->SetHighlightColorRGB(100, 200, 255);
    else if (element == "Rock")
        text->SetHighlightColorRGB(160, 82, 45);
    else if (element == "Poison")
        text->SetHighlightColorRGB(148, 0, 211);
    else if (element == "Normal")
        text->SetHighlightColorRGB(192, 192, 192);
    else if (element == "Flying")
        text->SetHighlightColorRGB(135, 206, 250);
    else if (element == "Psychic")
        text->SetHighlightColorRGB(255, 105, 180);
    else if (element == "Ghost")
        text->SetHighlightColorRGB(123, 104, 238);
    else if (element == "Dragon")
        text->SetHighlightColorRGB(0, 0, 205);
    else if (element == "Bug")
        text->SetHighlightColorRGB(154, 205, 50);
    else if (element == "Ground")
        text->SetHighlightColorRGB(210, 180, 140);
    else if (element == "Fighting")
        text->SetHighlightColorRGB(178, 34, 34);
    else
        text->SetHighlightColorRGB(255, 255, 255);

}



SkillUIState::~SkillUIState()
{
}

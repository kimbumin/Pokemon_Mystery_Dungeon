#include "SkillUIState.h"

#include "ImageGDIPlusManager.h"
#include "Timer.h"
#include "UIManager.h"
#include "UIElementText.h"

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

        skillUI.SkillName->SetFont(L"Arial", 18);
        skillUI.SkillCount->SetFont(L"Arial", 18);
        skillUI.SkillMaxCount->SetFont(L"Arial", 18);

        skillUI.SkillName->SetParent(SkillBox);
        skillUI.SkillCount->SetParent(SkillBox);
        skillUI.SkillMaxCount->SetParent(SkillBox);

        SkillList.push_back(skillUI);
    }

    

     // 테스트용
    std::vector<SkillDisplayData> testSkills = {{L"울음소리", 20, 20},
                                                {L"몸통박치기", 15, 20},
                                                {L"스파크", 10, 15},
                                                {L"철벽", 5, 5}};
    SetSkills(testSkills);


    // 서브
    SubCursor = new UIElementImage();
    SubCursor->SetImage(CursorImage);
    SubCursor->SetParent(SkillAssistBox);

    for (int i = 0; i < 3; ++i)
    {
        SubText[i] = new UIElementText();
        SubText[i]->SetFont(L"Arial", 18);
        SubText[i]->SetText(subMenu[i]);
        SubText[i]->SetParent(SkillAssistBox);
        SubText[i]->SetLocalPos(50, SubOffsetY[i]);
    }


    UpdateRealPos();

    return S_OK;
}

void SkillUIState::Release()
{
}

void SkillUIState::Update()
{
    fadeOutTime += TimerManager::GetInstance()->GetDeltaTime();
    fadeInTime = (sinf(fadeOutTime * 6.0f) * 0.5f) + 0.5f;

    if (!isSkillUseBox)
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
        {
            YIndex = (YIndex + 1) % 4;
            Cursor->SetLocalPos(25, OffsetY[YIndex]);
            Cursor->UpdateRealPos();
        }
        else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
        {
            YIndex = (YIndex - 1 + 4) % 4;
            Cursor->SetLocalPos(25, OffsetY[YIndex]);
            Cursor->UpdateRealPos();
        }
    }
    else
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
        {
            subCorsorIndex = (subCorsorIndex + 1) % 3;
            SubCursor->SetLocalPos(25, SubOffsetY[subCorsorIndex]);
            SubCursor->UpdateRealPos();
        }
        else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
        {
            subCorsorIndex = (subCorsorIndex - 1 + 3) % 3;
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
                    isSkillUseBox = false;
                    UIManager::GetInstance()->ChangeState("IdleUI");
                    break;
                case 1:  // 스킬 정보
                    UIManager::GetInstance()->ChangeState("SkillUseUI");
                    break;
                case 2:  // 스킬 취소
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
    // 스킬 사용 로직 추가
    if (index < 0 || index >= SkillList.size())
    {
        return;
    }
}

SkillUIState::~SkillUIState()
{
}

#include "InventoryUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIManager.h"

HRESULT InventoryUIState::Init()
{
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto InventoryBoxImage = manager.AddImage(
        "InventoryBox", L"Image/UIImage/InventoryUIState/InventoryBox.png");
    auto CursorImage = manager.AddImage(
        "Cursor", L"Image/UIImage/InventoryUIState/Cursor.png");
    auto ItemNameTextImage = manager.AddImage(
        "ItemNameText", L"Image/UIImage/InventoryUIState/ItemNameText.png");
    auto ItemDescriptionTextImage = manager.AddImage(
        "ItemDescriptionText",
        L"Image/UIImage/InventoryUIState/ItemDescriptionText.png");
    auto OtherInterfaceInfoBoxImage = manager.AddImage(
        "OtherInterfaceInfoBox",
        L"Image/UIImage/DefaultUIState/OtherInterfaceInfoBox.png");
    auto FakeCursorImage = manager.AddImage(
        "FakeCursor", L"Image/UIImage/DefaultUIState/Cursor.png");

    // UI 엘리먼트 생성
    InventoryBox = new UIElementImage();
    Cursor = new UIElementImage();
    OtherInterfaceInfoBox = new UIElementImage();
    SkillText = new UIElementText();
    ItemText = new UIElementText();
    SettingText = new UIElementText();
    FakeCursor = new UIElementImage();

    ItemNameText = new UIElementText();
    ItemNameText2 = new UIElementText();

    // UI 엘리먼트 설정
    InventoryBox->SetImage(InventoryBoxImage);
    InventoryBox->SetLocalPos(InventoryBoxPosX, InventoryBoxPosY);
    InventoryBox->setAlpha(0.95f);
    InventoryBox->SetParent(this);
    Cursor->SetImage(CursorImage);
    Cursor->SetLocalPos(CursorPosX, CursorPosY[0]);
    Cursor->SetParent(InventoryBox);

    ItemNameText->SetLocalPos(100, 95);
    ItemNameText->SetParent(InventoryBox);
    ItemNameText->SetText(L"Monter Ball");

    ItemNameText2->SetLocalPos(100, 140);
    ItemNameText2->SetParent(InventoryBox);
    ItemNameText2->SetText(L"Cookie");


    // 투명도 설정
    InventoryBox->setAlpha(0.95f);
    
    // 눈속임
    OtherInterfaceInfoBox->SetImage(OtherInterfaceInfoBoxImage);
    OtherInterfaceInfoBox->SetLocalPos(25, 10);
    OtherInterfaceInfoBox->setAlpha(0.8f);
    OtherInterfaceInfoBox->SetParent(this);

    SkillText->SetText(L"Skill");
    SkillText->SetFont(18);
    SkillText->SetTextLine(5.0f);
    SkillText->SetLocalPos(50, 30);
    SkillText->SetParent(OtherInterfaceInfoBox);

    ItemText->SetText(L"Item");
    ItemText->SetFont(18);
    ItemText->SetTextLine(5.0f);
    ItemText->SetLocalPos(50, 70);
    ItemText->SetParent(OtherInterfaceInfoBox);

    SettingText->SetText(L"Setting");
    SettingText->SetFont(18);
    SettingText->SetTextLine(5.0f);
    SettingText->SetLocalPos(50, 110);
    SettingText->SetParent(OtherInterfaceInfoBox);

    FakeCursor->SetImage(FakeCursorImage);
    FakeCursor->SetLocalPos(25, 70);
    FakeCursor->SetParent(OtherInterfaceInfoBox);
    FakeCursor->setAlpha(0.95f);


    return S_OK;
}

void InventoryUIState::Release()
{
}

void InventoryUIState::Update()
{
    fadeOutTime += TimerManager::GetInstance()->GetDeltaTime();
    fadeInTime = (sinf(fadeOutTime * 6.0f) * 0.5f) + 0.5f;

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex + 1) % 2;
        Cursor->SetLocalPos(CursorPosX, CursorPosY[YIndex]);
        Cursor->UpdateRealPos();
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex - 1 + 2) % 2;
        Cursor->SetLocalPos(CursorPosX, CursorPosY[YIndex]);
        Cursor->UpdateRealPos();
    }


    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X' 키
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        UIManager::GetInstance()->ChangeState("defaultUI");
    }


    Cursor->setAlpha(fadeInTime);
}

void InventoryUIState::Render(HDC hdc)
{
    if (OtherInterfaceInfoBox)
    {
        OtherInterfaceInfoBox->Render(hdc);
    }
    if (InventoryBox)
    {
        InventoryBox->Render(hdc);
    }
}

InventoryUIState::~InventoryUIState()
{
}

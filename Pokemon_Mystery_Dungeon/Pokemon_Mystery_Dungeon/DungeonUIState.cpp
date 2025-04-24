#include "DungeonUIState.h"

#include "ImageGDIPlusManager.h"
#include "UIManager.h"
#include "DungeonScene.h"

HRESULT DungeonUIState::Init()
{
    // 이미지
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto DungeonInfoBoxImage = manager.AddImage(
        "DungeonInfoBox", L"Image/UIImage/DungeonUIState/DungeonInfoBox.png");
    auto CursorImage =
        manager.AddImage("Cursor", L"Image/UIImage/DungeonUIState/Cursor.png");
    auto IceTypeImage = manager.AddImage(
        "IceType", L"Image/UIImage/DungeonUIState/IceType.png");
    auto MagmaTypeImage = manager.AddImage(
        "MagmaType", L"Image/UIImage/DungeonUIState/MagmaType.png");
    auto ForestTypeImage = manager.AddImage(
        "WaterTypeGif", L"Image/UIImage/DungeonUIState/ForestType.png");


    // UI 엘리먼트 생성
    DungeonInfoBox = new UIElementImage();
    DungeonInfoBox->SetImage(DungeonInfoBoxImage);
    DungeonInfoBox->SetLocalPos(25, 100);
    DungeonInfoBox->setAlpha(0.95f);
    DungeonInfoBox->SetParent(this);

    Cursor = new UIElementImage();
    Cursor->SetImage(CursorImage);
    Cursor->SetLocalPos(30, OffsetY[0]);
    Cursor->SetParent(DungeonInfoBox);

    IceType = new UIElementImage();
    IceType->SetImage(IceTypeImage);
    IceType->SetLocalPos(18, OffsetImageY[0]);
    IceType->setAlpha(0.5f);
    IceType->SetParent(DungeonInfoBox);

    MagmaType = new UIElementImage();
    MagmaType->SetImage(MagmaTypeImage);
    MagmaType->SetLocalPos(18, OffsetImageY[1]);
    MagmaType->setAlpha(0.5f);
    MagmaType->SetParent(DungeonInfoBox);

    ForestType = new UIElementImage();
    ForestType->SetImage(ForestTypeImage);
    ForestType->SetLocalPos(18, OffsetImageY[2]);
    ForestType->setAlpha(0.5f);
    ForestType->SetParent(DungeonInfoBox);

    int parentWidth = DungeonInfoBox->GetImageWidth();

    // 자식 객체 생성 waterType
    //WaterType = new UIElementImage();
    //WaterType->SetImage(WaterTypeGifImage);
    //WaterType->SetLocalPos(parentWidth - 120, OffsetY[0]);
    //WaterType->setAlpha(0.5f);
    //WaterType->SetSpeed(0.5f);
    //WaterType->setScale(0.17f, 0.17f);
    //WaterType->SetParent(DungeonInfoBox);

    // 자식 객체 생성 waterTypeText
    IceTypeText = new UIElementText();
    IceTypeText->SetText(L"Ice Dungeon");
    IceTypeText->SetLocalPos(50, OffsetY[0]);
    IceTypeText->SetParent(DungeonInfoBox);

    // 자식 객체 생성 fireType
    //FireType = new UIElementImage();
    //FireType->SetImage(FireTypeGifImage);
    //FireType->SetLocalPos(parentWidth - 120, OffsetY[1]);
    //FireType->setAlpha(0.5f);
    //FireType->SetSpeed(0.5f);
    //FireType->setScale(0.17f, 0.17f);
    //FireType->SetParent(DungeonInfoBox);

    // 자식 객체 생성 fireTypeText
    MagmaTypeText = new UIElementText();
    MagmaTypeText->SetText(L"Magma Dungeon");
    MagmaTypeText->SetLocalPos(50, OffsetY[1]);
    MagmaTypeText->SetParent(DungeonInfoBox);

    // 자식 객체 생성 forestTypeText
    ForestTypeText = new UIElementText();
    ForestTypeText->SetText(L"Forest Dungeon");
    ForestTypeText->SetLocalPos(50, OffsetY[2]);
    ForestTypeText->SetParent(DungeonInfoBox);


    UpdateRealPos();
    return S_OK;
}

void DungeonUIState::Release()
{
}

void DungeonUIState::Update()
{
    if(KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex + 1) % 3;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex - 1 + 3) % 3;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A)) // z키
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        if (YIndex == 0)
        {

            UIManager::GetInstance()->SetDungeonType(DUNGEON_TYPE_ICE);
            UIManager::GetInstance()->ChangeState("IdleUI");
            SceneManager::GetInstance()->AddScene("DungeonScene", new DungeonScene);
            SceneManager::GetInstance()->ChangeScene("DungeonScene");

        }
        else if (YIndex == 1)
        {
            UIManager::GetInstance()->SetDungeonType(DUNGEON_TYPE_MAGMA);
            UIManager::GetInstance()->ChangeState("IdleUI");
            SceneManager::GetInstance()->AddScene("DungeonScene",
                                                  new DungeonScene);
            SceneManager::GetInstance()->ChangeScene("DungeonScene");

        }
        else if (YIndex == 2)
        {
            UIManager::GetInstance()->SetDungeonType(DUNGEON_TYPE_FOREST);
            UIManager::GetInstance()->ChangeState("IdleUI");
            SceneManager::GetInstance()->AddScene("DungeonScene",
                                                  new DungeonScene);
            SceneManager::GetInstance()->ChangeScene("DungeonScene");
        }
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X' 키
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        UIManager::GetInstance()->CloseUIStateBox("DungeonUI");
    }

}

void DungeonUIState::Render(HDC hdc)
{
    if (DungeonInfoBox)
    {
        DungeonInfoBox->Render(hdc);
    }

}

DungeonUIState::~DungeonUIState()
{
}

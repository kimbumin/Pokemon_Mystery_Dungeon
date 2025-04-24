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
    //auto WaterTypeGifImage = manager.AddImage(
    //    "WaterType", L"Image/UIImage/DungeonUIState/waterType.gif", 1, 1, true);
    //auto FireTypeGifImage = manager.AddImage(
    //    "FireType", L"Image/UIImage/DungeonUIState/fireType.gif", 1, 1, true);

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
        YIndex = (YIndex + 1) % 3;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
    {
        YIndex = (YIndex - 1 + 3) % 3;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A)) // z키
    {
        if (YIndex == 0)
        {

            UIManager::GetInstance()->SetDungeonType(DUNGEON_TYPE_ICE);
            UIManager::GetInstance()->ChangeState("IdleUI");
            SceneManager::GetInstance()->AddScene("DungeonScene", new DungeonScene);
            SceneManager::GetInstance()->ChangeScene("DungeonScene");

            SoundManager::GetInstance()->StopBGM();
            SoundManager::GetInstance()->PlayBGM("ice");
        }
        else if (YIndex == 1)
        {
            UIManager::GetInstance()->SetDungeonType(DUNGEON_TYPE_MAGMA);
            UIManager::GetInstance()->ChangeState("IdleUI");
            SceneManager::GetInstance()->AddScene("DungeonScene",
                                                  new DungeonScene);
            SceneManager::GetInstance()->ChangeScene("DungeonScene");

            SoundManager::GetInstance()->StopBGM();
            SoundManager::GetInstance()->PlayBGM("magma");

        }
        else if (YIndex == 2)
        {
            UIManager::GetInstance()->SetDungeonType(DUNGEON_TYPE_FOREST);
            UIManager::GetInstance()->ChangeState("IdleUI");
            SceneManager::GetInstance()->AddScene("DungeonScene",
                                                  new DungeonScene);
            SceneManager::GetInstance()->ChangeScene("DungeonScene");

            SoundManager::GetInstance()->StopBGM();
            SoundManager::GetInstance()->PlayBGM("forest");
        }
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X' 키
    {
        UIManager::GetInstance()->CloseUIStateBox("DungeonUI");
    }

}

void DungeonUIState::Render(HDC hdc)
{
    if (DungeonInfoBox)
    {
        DungeonInfoBox->Render(hdc);
    }

    if (WaterType)
    {
        WaterType->Render(hdc);
    }
    if (FireType)
    {
        FireType->Render(hdc);
    }
}

DungeonUIState::~DungeonUIState()
{
}

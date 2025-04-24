#include "DefaultUIState.h"
#include "ImageGDIPlusManager.h"
#include "SkillUIState.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIManager.h"
#include "PlayerManager.h"
#include "PokemonPlayer.h"
#include "ISkill.h"
#include "CommonFunction.h"
#include "SquareScene.h"
#include "DungeonScene.h"
#include "PlayerInfoUIRender.h"

HRESULT DefaultUIState::Init()
{
    // 이미지
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto OtherInterfaceInfoBoxImage = manager.AddImage(
        "OtherInterfaceInfoBox",
        L"Image/UIImage/DefaultUIState/OtherInterfaceInfoBox.png");
    auto PokemonInfoBoxImage = manager.AddImage(
        "PokemonInfoBox", L"Image/UIImage/DefaultUIState/PokemonInfoBox.png");
    auto MapInfoBoxImage = manager.AddImage(
        "MapInfoBox", L"Image/UIImage/DefaultUIState/MapInfoBox.png");
    auto CursorImage =
        manager.AddImage("Cursor", L"Image/UIImage/DefaultUIState/Cursor.png");


    // UI 엘리먼트 생성
    OtherInterfaceInfoBox = new UIElementImage();
    PokemonInfoBox = new UIElementImage();
    MapInfoBox = new UIElementImage();
    Cursor = new UIElementImage();
    SkillText = new UIElementText();
    ItemText = new UIElementText();
    SettingText = new UIElementText();
    MapNameText = new UIElementText();
    PokemonNameText = new UIElementText();
    PokemonLevelText = new UIElementText();
    PokemonHPText = new UIElementText();
    AtkText = new UIElementText();
    DefText = new UIElementText();
    SpAtkText = new UIElementText();
    SpDefText = new UIElementText();
    SpeedText = new UIElementText();
    TypeText = new UIElementText();
    SumText = new UIElementText();
    AvgText = new UIElementText();



    UIElementText* texts[] = {PokemonNameText, PokemonLevelText, PokemonHPText,
                              AtkText,         DefText,          SpAtkText,
                              SpDefText,       SpeedText,        TypeText,
                              SumText,         AvgText};
    const wchar_t* labels[] = {L"Name", L"Level", L"HP",    L"ATK",
                               L"DEF",  L"SpATK", L"SpDEF", L"SPD",
                               L"TYPE", L"SUM",   L"AVG"};

    for (int i = 0; i < 11; ++i)
    {
        texts[i]->SetFont(18);
        texts[i]->SetTextLine(5.0f);
        texts[i]->SetParent(PokemonInfoBox);
    }



    OtherInterfaceInfoBox->SetImage(OtherInterfaceInfoBoxImage);
    PokemonInfoBox->SetImage(PokemonInfoBoxImage);
    MapInfoBox->SetImage(MapInfoBoxImage);
    Cursor->SetImage(CursorImage);

    /*--------------- 텍스트 설정 ---------------*/
    // otherBox
    SkillText->SetText(L"Skill");
    SkillText->SetFont(18);
    SkillText->SetTextLine(5.0f);
    SkillText->SetLocalPos(fontPosX, OffsetY[0]);
    SkillText->SetParent(OtherInterfaceInfoBox);

    ItemText->SetText(L"Item");
    ItemText->SetFont(18);
    ItemText->SetTextLine(5.0f);
    ItemText->SetLocalPos(fontPosX, OffsetY[1]);
    ItemText->SetParent(OtherInterfaceInfoBox);

    SettingText->SetText(L"Setting");
    SettingText->SetFont(18);
    SettingText->SetTextLine(5.0f);
    SettingText->SetLocalPos(fontPosX, OffsetY[2]);
    SettingText->SetParent(OtherInterfaceInfoBox);

    // mapBox
    MapNameText->SetText(L"마을");
    MapNameText->SetFont(18);
    MapNameText->SetTextLine(5.0f);
    MapNameText->SetLocalPos(50, MapInfoBox->GetImageHeight() / 2 - 10);
    MapNameText->SetParent(MapInfoBox);

    // pokemonInfoBox
    //PokemonNameText->SetFont(18);
    //PokemonNameText->SetTextLine(5.0f);
    //PokemonNameText->SetTextColorRGB(241, 179, 0);  // #F1B300
    //PokemonNameText->SetLocalPos(50, 30);
    //PokemonNameText->SetParent(PokemonInfoBox);

    //PokemonLevelText->SetFont(18);
    //PokemonLevelText->SetTextLine(5.0f);
    //PokemonLevelText->SetLocalPos(80,60);
    //PokemonLevelText->SetParent(PokemonInfoBox);

    //PokemonHPText->SetFont(18);
    //PokemonHPText->SetTextLine(5.0f);
    //PokemonHPText->SetLocalPos(80, 90);
    //PokemonHPText->SetParent(PokemonInfoBox);
    PokemonNameText->SetLocalPos(50, 30);
    PokemonLevelText->SetLocalPos(80, 60);
    PokemonHPText->SetLocalPos(80, 80);
    SpeedText->SetLocalPos(80, 100);
    AtkText->SetLocalPos(160, 60);
    DefText->SetLocalPos(240, 60);
    TypeText->SetLocalPos(320, 60);
    SpAtkText->SetLocalPos(200, 80);
    SpDefText->SetLocalPos(200, 100);
    SumText->SetLocalPos(320, 100);
    AvgText->SetLocalPos(320, 80);

   

    /*--------------- 텍스트 설정 끝 ---------------*/

    // UI 엘리먼트 위치 설정
    OtherInterfaceInfoBox->SetLocalPos(25, 10);
    MapInfoBox->SetLocalPos((GameViewSize_X - MapInfoBoxImage->GetWidth()) - 25,
                            40);
    PokemonInfoBox->SetLocalPos(25, GameViewSize_Y - 170);
    Cursor->SetLocalPos(25, OffsetY[YIndex]);

    // 투명도 설정
    OtherInterfaceInfoBox->setAlpha(0.95f);
    MapInfoBox->setAlpha(0.95f);
    PokemonInfoBox->setAlpha(0.95f);

    // 이미지 크기 좀 조정함
    OtherInterfaceInfoBox->setScale(1.0f, 1.0f);
    MapInfoBox->setScale(1.0f, 1.0f);
    PokemonInfoBox->setScale(1.0f, 1.0f);

    // 부모 객체로 설정
    OtherInterfaceInfoBox->SetParent(this);
    PokemonInfoBox->SetParent(this);
    MapInfoBox->SetParent(this);

    // 부모위치 상속받는 자식 객체
    Cursor->SetParent(OtherInterfaceInfoBox);

    UpdateRealPos();

    return S_OK;
}

void DefaultUIState::Release()
{
}

void DefaultUIState::Update()
{
    fadeOutTime += TimerManager::GetInstance()->GetDeltaTime();
    fadeInTime = (sinf(fadeOutTime * 6.0f) * 0.5f) + 0.5f;

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
    {
        //SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex + 1) % 3;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
    {
        //SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex - 1 + 3) % 3;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }

    Cursor->setAlpha(fadeInTime);

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A))
    {
        if (YIndex == 0)
        {
            UIManager::GetInstance()->ChangeState("SkillUI");
        }
        else if (YIndex == 1)
        {
            UIManager::GetInstance()->ChangeState("InventoryUI");
        }
        else if (YIndex == 2)
        {
            UIManager::GetInstance()->ChangeState("SettingUI");
        }
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        UIManager::GetInstance()->ChangeState("IdleUI");
    }

    PlayerInfoTextSetting();
}

void DefaultUIState::Render(HDC hdc)
{
    OtherInterfaceInfoBox->Render(hdc);
    PokemonInfoBox->Render(hdc);
    MapInfoBox->Render(hdc);
    Cursor->Render(hdc);
}

void DefaultUIState::PlayerInfoTextSetting()
{
    PlayerInfoUIRenderer::SetBasicStats(PokemonNameText, PokemonLevelText,
                                        PokemonHPText);
    PlayerInfoUIRenderer::SetDetailedStats(AtkText, DefText, SpAtkText,
                                           SpDefText, SpeedText, SumText,
                                           AvgText, TypeText);

    DungeonType type = UIManager::GetInstance()->GetDungeonType();
    MapNameText->SetText(GetMapNameByType(type));
    SetMapNameTextStyle(MapNameText, type);
}

wstring DefaultUIState::GetMapNameByType(DungeonType type)
{
    Scene* scene = SceneManager::currentScene;

    if (dynamic_cast<SquareScene*>(scene))
    {
        return L"Village";
    }
    else if (dynamic_cast<DungeonScene*>(scene))
    {
        DungeonType type = UIManager::GetInstance()->GetDungeonType();
        switch (type)
        {
            case DUNGEON_TYPE_ICE:
                return L"Ice Cavern";
            case DUNGEON_TYPE_MAGMA:
                return L"Magma Volcano";
            case DUNGEON_TYPE_FOREST:
                return L"Forest Trail";
            default:
                return L"Unknown Dungeon";
        }
    }

    return L"Unknown Map";
}

void DefaultUIState::SetMapNameTextStyle(UIElementText* text, DungeonType type)
{
    Scene* scene = SceneManager::currentScene;

    if (dynamic_cast<SquareScene*>(scene))
    {
        text->SetTextColorRGB(255, 215, 0);  // 노란 느낌 (마을)
    }
    else if (dynamic_cast<DungeonScene*>(scene))
    {
        DungeonType type = UIManager::GetInstance()->GetDungeonType();

        switch (type)
        {
            case DUNGEON_TYPE_ICE:
                text->SetTextColorRGB(0, 120, 200);  // 진한 블루
                break;
            case DUNGEON_TYPE_MAGMA:
                text->SetTextColorRGB(200, 40, 40);  // 진한 레드
                break;
            case DUNGEON_TYPE_FOREST:
                text->SetTextColorRGB(34, 139, 34);  // 포레스트 그린
                break;
            default:
                text->SetTextColorRGB(255, 255, 255);  // 기본
                break;
        }
    }
    else
    {
        text->SetTextColorRGB(255, 255, 255);  // 안전용
    }
}

DefaultUIState::~DefaultUIState()
{
}

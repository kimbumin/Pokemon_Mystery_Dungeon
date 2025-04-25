#include "InfoUIState.h"

#include "ImageGDIPlusManager.h"
#include "ImageManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "Image.h"
#include "PlayerManager.h"
#include "PokemonPlayer.h"
#include "CommonFunction.h"

HRESULT InfoUIState::Init()
{
    auto& manager = *ImageManager::GetInstance();
    auto FirstInfoBoxImage = manager.AddImage(
        "FirstInfoBox", L"Image/UIImage/InfoUIState/ExistsInfoBox.bmp", 300,
        50);
    auto SecondInfoBoxImage = manager.AddImage(
        "SecondInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.bmp", 300,
        50);
    auto ThirdInfoBoxImage = manager.AddImage(
        "ThirdInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.bmp", 300,
        50);
    auto FourthInfoBoxImage = manager.AddImage(
        "FourthInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.bmp", 300,
        50);
    auto playerImageBoxImage = manager.AddImage(
        "PlayerImageBox", L"Image/UIImage/InfoUIState/PlayerImage.bmp", 25,
        30,true,RGB(255,0,255));
    auto BottomRightImage = manager.AddImage(
        "BottomRight", L"Image/UIImage/InfoUIState/BottomRightImage.bmp", 300, 200);

    auto CurrHpBarImage = manager.AddImage(
        "CurrHpBar", L"Image/UIImage/InfoUIState/CurrHpBar.bmp", 50, 10);
    auto MaxHpBarImage = manager.AddImage(
        "MaxHpBar", L"Image/UIImage/InfoUIState/MaxHpBar.bmp", 56, 16);

    // UI 엘리먼트 생성
    FirstInfoBox = new UIElementImage();
    SecondInfoBox = new UIElementImage();
    ThirdInfoBox = new UIElementImage();
    FourthInfoBox = new UIElementImage();

    playerImageBox = new UIElementImage();

    BottomRight = new UIElementImage();
    

    CurrHpBar = new UIElementImage();
    MaxHpBar = new UIElementImage();

    FirstInfoBox->SetImage(FirstInfoBoxImage);
    SecondInfoBox->SetImage(SecondInfoBoxImage);
    ThirdInfoBox->SetImage(ThirdInfoBoxImage);
    FourthInfoBox->SetImage(FourthInfoBoxImage);

    playerImageBox->SetImage(playerImageBoxImage);

    BottomRight->SetImage(BottomRightImage);

    CurrHpBar->SetImage(CurrHpBarImage);
    MaxHpBar->SetImage(MaxHpBarImage);

    // UI 엘리먼트 위치 설정
    FirstInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[0]);
    SecondInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[1]);
    ThirdInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[2]);
    FourthInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[3]);

    playerImageBox->SetLocalPos(15, InfoBoxPosYOffset[0]/2 + 12);

    BottomRight->SetLocalPos(InfoBoxPosX, 200);

    MaxHpBar->SetLocalPos(710, 18);
    CurrHpBar->SetLocalPos(713, 21);

    FirstInfoBox->SetParent(this);
    SecondInfoBox->SetParent(this);
    ThirdInfoBox->SetParent(this);
    FourthInfoBox->SetParent(this);

    playerImageBox->SetParent(FirstInfoBox);
    BottomRight->SetParent(this);

    MaxHpBar->SetParent(nullptr);
    CurrHpBar->SetParent(nullptr);


    // 이름
    NameText = new UIElementText();
    NameText->SetFont(12);
    NameText->SetTextColorRGB(255, 204, 0);  // 노란색 느낌
    NameText->SetLocalPos(80, 5);
    NameText->SetParent(FirstInfoBox);

    // 레벨
    LevelText = new UIElementText();
    LevelText->SetFont(12);
    LevelText->SetTextColorRGB(255, 255, 255);  // 흰색
    LevelText->SetLocalPos(100,20);
    LevelText->SetParent(FirstInfoBox);

    // HP
    HPText = new UIElementText();
    HPText->SetFont(12);
    HPText->SetTextColorRGB(255, 255, 255);  // 주황 강조색
    HPText->SetLocalPos(160, 20);
    HPText->SetParent(FirstInfoBox);

    // 초기 포켓몬 정보 설정
    PokemonPlayer* player = PlayerManager::GetInstance()->GetPlayer();
    if (player)
        SetPlayerInfo(player);

    UpdateRealPos();

    return S_OK;
}

void InfoUIState::Release()
{
}

void InfoUIState::Update()
{
    if (player)
    {
        currentHP = player->GetCurrentHp();
        currentHP = max(0, currentHP);  // 음수 방지
        maxHP = player->GetCurrentPokemonData()
                    .hp;  // 매 프레임 최대HP도 업데이트 (레벨업 등 대응)
        percent = maxHP > 0 ? static_cast<float>(currentHP) / maxHP : 0.0f;

        barWidth = static_cast<int>(CurrHpBar->GetImageWidth() * percent);
        barHeight = CurrHpBar->GetImageHeight();

        HPText->SetText(to_wstring(currentHP) + L"/" + to_wstring(maxHP));
    }
}

void InfoUIState::Render(HDC hdc)
{

    FirstInfoBox->Render(hdc);
    SecondInfoBox->Render(hdc);
    ThirdInfoBox->Render(hdc);
    FourthInfoBox->Render(hdc);
    BottomRight->Render(hdc);
    MaxHpBar->Render(hdc);
    CurrHpBar->RenderPartial(hdc,  barWidth, barHeight);
    

    // 텍스트 렌더링
    NameText->Render(hdc);
    LevelText->Render(hdc);
    HPText->Render(hdc);
}

InfoUIState::~InfoUIState()
{
}

void InfoUIState::SetInfoBoxText(int index, const wstring& text)
{
}

void InfoUIState::SetPlayerInfo(PokemonBase* playerPokemon)
{
    player = playerPokemon;

    if (!player)
        return;

    NameText->SetText(ToWString(player->GetCurrentPokemonData().name));
    LevelText->SetText(L"Lv. " + to_wstring(player->GetLevel()));

    maxHP = player->GetCurrentPokemonData().hp;
    currentHP = player->GetCurrentHp();
    currentHP = max(0, currentHP);  // 음수 방지
    percent = maxHP > 0 ? static_cast<float>(currentHP) / maxHP : 0.0f;

    HPText->SetText(to_wstring(currentHP) + L"/" + to_wstring(maxHP));
}

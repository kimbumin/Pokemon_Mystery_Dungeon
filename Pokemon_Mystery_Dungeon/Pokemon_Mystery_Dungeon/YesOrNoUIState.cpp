#include "YesOrNoUIState.h"

#include "ImageGDIPlusManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"

HRESULT YesOrNoUIState::Init()
{
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto YesOrNoBoxImage = manager.AddImage(
        "YesOrNoBox", L"Image/UIImage/YesOrNoUIState/YesOrNoBox.png");
    auto CursorImage =
        manager.AddImage("Cursor", L"Image/UIImage/YesOrNoUIState/Cursor.png");
    // UI 엘리먼트 생성
    YesOrNoBox = new UIElementImage();
    YesText = new UIElementText();
    NoText = new UIElementText();
    Cursor = new UIElementImage();

    // UI 엘리먼트 설정
    YesOrNoBox->SetImage(YesOrNoBoxImage);
    Cursor->SetImage(CursorImage);

    YesText->SetText(L"Yes");
    NoText->SetText(L"No");

    // UI 엘리먼트 위치 설정
    YesOrNoBox->SetLocalPos(InfoBoxPosX, 200);
    YesText->SetLocalPos(40, InfoBoxPosYOffset[0]);
    NoText->SetLocalPos(40, InfoBoxPosYOffset[1]);

    Cursor->SetLocalPos(20, InfoBoxPosYOffset[0] + 5);

    // 알파
    YesOrNoBox->setAlpha(0.7f);

    // 부모 설정
    YesOrNoBox->SetParent(this);

    // 자식
    YesText->SetParent(YesOrNoBox);
    NoText->SetParent(YesOrNoBox);
    Cursor->SetParent(YesOrNoBox);

    UpdateRealPos();
    return S_OK;
}

void YesOrNoUIState::Release()
{
}

void YesOrNoUIState::Update()
{
}

void YesOrNoUIState::Render(HDC hdc)
{
    YesOrNoBox->Render(hdc);
}

YesOrNoUIState::~YesOrNoUIState()
{
}

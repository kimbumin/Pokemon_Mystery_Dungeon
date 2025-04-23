#include "DownStairUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"

HRESULT DownStairUIState::Init()
{
    auto manager = *ImageGDIPlusManager::GetInstance();
    auto DownStairBoxImage = manager.AddImage("DownStairBox", L"Image/UIImage/DownStairUIState/DownStairBox.png");
    auto CursorImage = manager.AddImage("Cursor", L"Image/UIImage/DownStairUIState/Cursor.png");

    DownStairBox = new UIElementImage();
    DownStairBox->SetImage(DownStairBoxImage);
    DownStairBox->SetLocalPos(25, 200);
    DownStairBox->setAlpha(0.95f);
    DownStairBox->SetParent(this);

    Cursor = new UIElementImage();
    Cursor->SetImage(CursorImage);
    Cursor->SetLocalPos(25, OffsetY[0]);
    Cursor->SetParent(DownStairBox);
    Cursor->setAlpha(0.95f);

    // 자식 객체 생성
    IsDownText = new UIElementText();
    IsDownText->SetText(L"Would you like to go down the stairs?");
    IsDownText->SetFont(L"Arial", 18);
    IsDownText->SetTextLine(5.0f);
    IsDownText->SetLocalPos(50, OffsetY[0]);
    IsDownText->SetParent(DownStairBox);

    YesText = new UIElementText();
    YesText->SetText(L"Yes");
    YesText->SetFont(L"Arial", 18);
    YesText->SetTextLine(5.0f);
    YesText->SetLocalPos(50, OffsetY[0]);
    YesText->SetParent(DownStairBox);

    NoText = new UIElementText();
    NoText->SetText(L"No");
    NoText->SetFont(L"Arial", 18);
    NoText->SetTextLine(5.0f);
    NoText->SetLocalPos(50, OffsetY[1]);
    NoText->SetParent(DownStairBox);



    return S_OK;
}

void DownStairUIState::Release()
{
}

void DownStairUIState::Update()
{
}

void DownStairUIState::Render(HDC hdc)
{
    if (DownStairBox)
    {
        DownStairBox->Render(hdc);
    }
}

DownStairUIState::~DownStairUIState()
{
}

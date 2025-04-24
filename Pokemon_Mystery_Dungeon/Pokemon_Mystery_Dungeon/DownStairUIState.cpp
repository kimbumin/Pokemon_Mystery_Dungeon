#include "DownStairUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "CoolDownManager.h"

HRESULT DownStairUIState::Init()
{
    auto manager = *ImageGDIPlusManager::GetInstance();
    auto DownStairBoxImage = manager.AddImage("DownStairBox", L"Image/UIImage/DownStairUIState/DownStairBox.png");
    auto YesOrNoBoxImage = manager.AddImage(
        "YesOrNoBox", L"Image/UIImage/DownStairUIState/YesOrNoBox.png");
    auto CursorImage = manager.AddImage("Cursor", L"Image/UIImage/DownStairUIState/Cursor.png");

    DownStairBox = new UIElementImage();
    DownStairBox->SetImage(DownStairBoxImage);
    DownStairBox->SetLocalPos(25, 200);
    DownStairBox->setAlpha(0.95f);
    DownStairBox->SetParent(this);

    YesOrNoBox = new UIElementImage();
    YesOrNoBox->SetImage(YesOrNoBoxImage);
    YesOrNoBox->SetLocalPos(DownStairBox->GetImageWidth() - 80, 0);
    YesOrNoBox->setAlpha(0.95f);
    YesOrNoBox->SetParent(DownStairBox);

    Cursor = new UIElementImage();
    Cursor->SetImage(CursorImage);
    Cursor->SetLocalPos(25, OffsetY[0]);
    Cursor->SetParent(YesOrNoBox);
    Cursor->setAlpha(0.95f);

    // 자식 객체 생성
    IsDownText = new UIElementText();
    IsDownText->SetText(L"Would you like to go down \n the stairs?");
    IsDownText->SetFont(18);
    IsDownText->SetTextLine(5.0f);
    IsDownText->SetLocalPos(50, OffsetY[0]);
    IsDownText->SetParent(DownStairBox);

    YesText = new UIElementText();
    YesText->SetText(L"Yes");
    YesText->SetFont(18);
    YesText->SetTextLine(5.0f);
    YesText->SetLocalPos(50, OffsetY[0]);
    YesText->SetParent(YesOrNoBox);

    NoText = new UIElementText();
    NoText->SetText(L"No");
    NoText->SetFont(18);
    NoText->SetTextLine(5.0f);
    NoText->SetLocalPos(50, OffsetY[1]);
    NoText->SetParent(YesOrNoBox);



    return S_OK;
}

void DownStairUIState::Release()
{
}

void DownStairUIState::Update()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
    {
        YIndex = (YIndex + 1) % 2;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
    {
        YIndex = (YIndex - 1 + 2) % 2;
        Cursor->SetLocalPos(25, OffsetY[YIndex]);
        Cursor->UpdateRealPos();
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A))  // z키
    {
        if (YIndex == 0)
        {
            isActive = true;
            UIManager::GetInstance()->ChangeState("IdleUI");
        }
        else if (YIndex == 1)
        {
            CoolDownManager::GetInstance()->SetCoolDown("DownStair", 3.0f);
            UIManager::GetInstance()->ChangeState("IdleUI");
        }
    }
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

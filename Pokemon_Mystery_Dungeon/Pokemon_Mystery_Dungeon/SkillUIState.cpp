#include "SkillUIState.h"
#include "ImageGDIPlusManager.h"
#include "Timer.h"
#include "UIManager.h"

HRESULT SkillUIState::Init()
{
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto SkillBoxImage = manager.AddImage("SkillBox", L"Image/UIImage/SkillUIState/SkillBox.png");
	auto SkillAssistBoxImage = manager.AddImage("SkillAssistBox", L"Image/UIImage/SkillUIState/SkillAssistBox.png");
	auto UseInfoBoxImage = manager.AddImage("UseInfoBox", L"Image/UIImage/SkillUIState/UseInfoBox.png");
	auto CursorImage = manager.AddImage("SkillInfoBoxCursor", L"Image/UIImage/SkillUIState/Cursor.png");

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
	SkillAssistBox->SetParent(SkillBox);
	UseInfoBox->SetParent(this);
	Cursor->SetParent(SkillBox);

	SkillBox->setAlpha(0.7f);
	UseInfoBox->setAlpha(0.7f);
	SkillAssistBox->setAlpha(0.7f);
	Cursor->SetLocalPos(25, OffsetY[YIndex]);
	SkillBox->SetLocalPos(25, 10);
	UseInfoBox->SetLocalPos(25, 250);
	SkillAssistBox->SetLocalPos(280, 48);

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

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
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

	if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A)) // Z
	{
		if (!isSkillUseBox)
		{
			isSkillUseBox = true;
		}
		else
		{
			UIManager::GetInstance()->ChangeState("SkillUseUI");
		}
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))
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

	Cursor->setAlpha(fadeInTime);
}

void SkillUIState::Render(HDC hdc)
{
	SkillBox->Render(hdc);
	UseInfoBox->Render(hdc);
	Cursor->Render(hdc);

	if (isSkillUseBox) {
		SkillAssistBox->Render(hdc);
	}
}

SkillUIState::~SkillUIState()
{
}

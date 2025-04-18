#include "SkillInfoUIState.h"
#include "ImageGDIPlusManager.h"
#include "Timer.h"


HRESULT SkillInfoUIState::Init()
{
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto skillInfoBoxImage = manager.AddImage("SkillInfoBox", L"Image/UIImage/SkillInfoUIState/SkillInfoBox.png");
	auto CursorImage = manager.AddImage("SkillInfoBoxCursor", L"Image/UIImage/SkillInfoUIState/Cursor.png");

	// UI 엘리먼트 생성
	SkillInfoBox = new UIElementImage();
	Cursor = new UIElementImage();

	SkillInfoBox->SetImage(skillInfoBoxImage);
	Cursor->SetImage(CursorImage);

	SkillInfoBox->SetParent(this);
	Cursor->SetParent(SkillInfoBox);

	SkillInfoBox->setAlpha(0.7f);
	SkillInfoBox->setScale(0.9f, 0.9f);
	Cursor->SetLocalPos(25, OffsetY[YIndex]);
	SkillInfoBox->SetLocalPos(25, 10);

	UpdateRealPos();
	

	return S_OK;
}

void SkillInfoUIState::Release()
{
}

void SkillInfoUIState::Update()
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

	Cursor->setAlpha(fadeInTime);
}

void SkillInfoUIState::Render(HDC hdc)
{
	SkillInfoBox->Render(hdc);
	Cursor->Render(hdc);
}

SkillInfoUIState::~SkillInfoUIState()
{
}

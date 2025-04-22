#include "SkillInfoUIState.h"
#include "UIManager.h"

HRESULT SkillInfoUIState::Init()
{
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto skillInfoBoxImage = manager.AddImage("SkillInfoBox", L"Image/UIImage/SkillInfoUIState/SkillInfoBox.png");

	SkillInfoBox = new UIElementImage();

	SkillInfoBox->SetImage(skillInfoBoxImage);

	SkillInfoBox->SetLocalPos(25, 10);

	SkillInfoBox->setAlpha(0.7f);

	UpdateRealPos();

    return S_OK;
}

void SkillInfoUIState::Release()
{
}

void SkillInfoUIState::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))
	{
		UIManager::GetInstance()->ChangeState("SkillUI");
	}
}

void SkillInfoUIState::Render(HDC hdc)
{
	SkillInfoBox->Render(hdc);
}

SkillInfoUIState::~SkillInfoUIState()
{
}

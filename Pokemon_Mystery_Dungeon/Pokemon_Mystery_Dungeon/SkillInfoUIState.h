#pragma once
#include "UIState.h"
#include "ImageGDIPlus.h"
#include "UIElementImage.h"

// 스킬 정보 UI
class SkillInfoUIState : public UIState, public UIElement
{
private:
	UIElementImage* SkillInfoBox = nullptr;
	UIElementImage* Cursor = nullptr;

	const int OffsetY[3] = { 50, 80, 110 };
	int YIndex = 0;
	float fadeOutTime = 0.0f;
	float fadeInTime = 1.0f;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~SkillInfoUIState() override;
};


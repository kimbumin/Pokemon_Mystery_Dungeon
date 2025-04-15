#pragma once
#include "UIState.h"

// 스킬 정보 UI
class SkillInfoUIState : public UIState
{
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~SkillInfoUIState() override;
};


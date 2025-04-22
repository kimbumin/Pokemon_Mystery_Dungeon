#pragma once
#include "UIState.h"

// Intro Animation(예비)
// 다른 UI 모두 구현 한 뒤 할 것.
class TitleUIState : public UIState
{
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~TitleUIState() override;
};


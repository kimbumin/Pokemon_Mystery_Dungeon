#pragma once
#include "UIState.h"

class DefaultUIState : public UIState
{
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~DefaultUIState() override;
};


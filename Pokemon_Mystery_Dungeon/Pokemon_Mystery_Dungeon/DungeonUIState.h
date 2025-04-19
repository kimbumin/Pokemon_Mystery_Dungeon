#pragma once
#include "UIState.h"
#include "ImageGDIPlus.h"
#include "UIElementImage.h"

class DungeonUIState : public UIState, public UIElement
{
private:
	UIElementImage* DungeonInfoBox = nullptr;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~DungeonUIState() override;
};


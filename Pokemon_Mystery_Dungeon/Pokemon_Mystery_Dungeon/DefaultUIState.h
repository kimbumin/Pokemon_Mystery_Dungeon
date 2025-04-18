#pragma once
#include "UIState.h"
#include "ImageGDIPlus.h"
#include "UIElementImage.h"



class DefaultUIState : public UIState, public UIElement
{
private:
	UIElementImage* OtherInterfaceInfoBox = nullptr;
	UIElementImage* PokemonInfoBox = nullptr;
	UIElementImage* MapInfoBox = nullptr;

	UIElementImage* Cursor = nullptr;
	
	const int OffsetY[3] = { 30, 70, 110 };
	int YIndex = 0;

	float fadeOutTime = 0.0f;
	float fadeInTime = 1.0f;

public:
	HRESULT Init() override;

	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~DefaultUIState() override;
};


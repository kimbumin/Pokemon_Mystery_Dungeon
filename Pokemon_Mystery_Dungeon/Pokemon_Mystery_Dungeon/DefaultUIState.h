#pragma once
#include "UIState.h"
#include "ImageGDIPlus.h"

class DefaultUIState : public UIState
{
private:
	ImageGDIPlus* defaultBoxImage = nullptr;

	int defaultImageX = 25;
	int defaultImageY = 50;

	bool isSlidingIn = true;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~DefaultUIState() override;
};


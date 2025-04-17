#pragma once
#include "UIState.h"
#include "ImageGDIPlus.h"

class DialogueUIState : public UIState
{
private:
	ImageGDIPlus* dialogueBoxImage = nullptr;
	int dialogueBoxX = -400;
	int dialogueBoxY = 240;
	bool isSlidingIn = true;

public:
	~DialogueUIState();
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};


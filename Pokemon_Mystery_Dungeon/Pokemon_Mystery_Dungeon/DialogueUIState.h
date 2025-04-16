#pragma once
#include "UIState.h"
#include "Image.h"

class DialogueUIState : public UIState
{
private:
	Image* dialogueBoxImage = nullptr;
	int dialogueBoxX = 50;
	int dialogueBoxY = 200;

public:
	~DialogueUIState();
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};


#pragma once
#include "GameObject.h"
#include "ImageGDIPlus.h"


class CameraTestScene : public GameObject
{
private:
	ImageGDIPlus* testMap = nullptr;

	bool isDialogueBoxOpen = false;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	
};


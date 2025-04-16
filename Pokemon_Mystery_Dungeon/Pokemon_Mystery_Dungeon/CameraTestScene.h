#pragma once
#include "GameObject.h"
#include "Image.h"


class CameraTestScene : public GameObject
{
private:
	Image* testMap = nullptr;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};


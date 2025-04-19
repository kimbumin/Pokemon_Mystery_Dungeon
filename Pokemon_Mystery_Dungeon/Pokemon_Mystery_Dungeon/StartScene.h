#pragma once
#include "GameObject.h"

class ImageGDIPlus;

class StartScene : public GameObject
{
public:

	virtual HRESULT Init() override;		
	virtual void Release()override;		
	virtual void Update()override;
	virtual void Render(HDC hdc)override;

	StartScene();
	virtual ~StartScene();

private:
	ImageGDIPlus* intro;
	std::vector<ImageGDIPlus*> introFrames;
	int currFrameIndex;
	float elapsedTime;
};


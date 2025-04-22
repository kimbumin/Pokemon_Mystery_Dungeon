#pragma once
#include "Scene.h"

class ImageGDIPlus;

class StartScene : public Scene
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


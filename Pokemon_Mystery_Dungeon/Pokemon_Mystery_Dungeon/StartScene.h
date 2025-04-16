#pragma once
#include "GameObject.h"
class StartScene : public GameObject
{
public:

	virtual HRESULT Init();		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	StartScene();
	virtual ~StartScene();

private:
	Image* backGround;

};


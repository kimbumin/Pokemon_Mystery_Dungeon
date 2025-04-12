#pragma once
#include "GameObject.h"

class SquareScene : public GameObject
{
public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	SquareScene() {};
	virtual ~SquareScene() {};




private:
	Image* backGround;
	Image* redFlower;
	Image* yellowFlower;

	int currAnimaionFrame;
	float elapsedTime;




};


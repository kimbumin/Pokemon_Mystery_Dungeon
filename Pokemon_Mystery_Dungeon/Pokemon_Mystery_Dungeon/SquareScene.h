#pragma once
#include "Scene.h"


class CollisionBoxTool;
class MPlayer;

class SquareScene : public Scene
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
	Image* river;

	MPlayer* mPlayer;
	CollisionBoxTool* collisionBoxTool;


	int currAnimaionFrame;
	float elapsedTime;

	wchar_t szText[128];
	void RenderFlowers(HDC hdc, Image* flower, const std::vector<POINT>& positions, int currFrame);

	std::vector<POINT> redPositions;
	std::vector<POINT> yellowPositions;


};


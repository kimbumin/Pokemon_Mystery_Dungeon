#pragma once
#include "GameObject.h"
#include "PlayerBumin.h"
#include "EnemyBumin.h"
#include "EmberSkill.h"

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
	Image* river;

	PlayerBumin* player; // 플레이어
	EnemyBumin* enemy;   // 적
	EmberSkill* emberSkill; // 스킬

	int currAnimaionFrame;
	float elapsedTime;

	wchar_t szText[128];
	void RenderFlowers(HDC hdc, Image* flower, const std::vector<POINT>& positions, int currFrame);

	std::vector<POINT> redPositions;
	std::vector<POINT> yellowPositions;


};


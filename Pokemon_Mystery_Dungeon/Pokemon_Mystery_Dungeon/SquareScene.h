#pragma once
#include "Scene.h"

class CollisionBoxTool;
class SkillManager;
class PokemonPlayer;
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
    PokemonPlayer* player;
    SkillManager* skillManager;

	int currAnimaionFrame;
	float elapsedTime;
    float fadeElapsedTime;

	wchar_t szText[128];
    void RenderFlowers(HDC hdc, Image* flower,
                       const std::vector<POINT>& positions, int currFrame);

    bool IsPlayerOnDungeonTrigger();

	std::vector<POINT> redPositions;
	std::vector<POINT> yellowPositions;

    CollisionBoxTool* collisionBoxTool;
};

#pragma once
#include "Scene.h"
#include "MPlayer.h"

class Boss;
class CollisionBoxTool;

class BossScene : public Scene
{
private:
    Boss* boss;
    MPlayer* mPlayer;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;

    void InitBoss();

    bool IsBossDefeated();

private:
    void CheckBattleEnd();
    int backGroundWidth;
    int backGroundHeight;
    Image* backGround;
    CollisionBoxTool* collisionBoxTool;


};
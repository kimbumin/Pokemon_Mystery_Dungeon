#pragma once
#include "Scene.h"

class DungeonManager;
class PokemonPool;
class Map;
class BattleSystem;
class BuminScene : public Scene
{
private:
    Map* dungeonMap;
    DungeonManager* dungeonManager;
    PokemonPool* pool;
    BattleSystem* battleSystem;

public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    BuminScene() {};
    virtual ~BuminScene() {};
};

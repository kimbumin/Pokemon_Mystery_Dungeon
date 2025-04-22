#pragma once
#include "Scene.h"

class DungeonManager;
class PokemonPool;
class Map;
class DongminScene : public Scene
{
private:
    Map* dungeonMap;
    DungeonManager* dungeonManager;
    PokemonPool* pool;

public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    DongminScene() {};
    virtual ~DongminScene() {};
};

#pragma once
#include "Scene.h"

class Player;
class MPlayer;
class Map;
class DungeonManager;
class PokemonPool;
class DungeonScene : public Scene
{
public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void GenerateNextFloor();

    POINT ConvertToPixel(POINT tilePos);

    bool IsPlayerOnStair();

    DungeonScene() {};
    virtual ~DungeonScene() {};

private:
    Image* sampleTile;
    Image* stairImage;


    Map* dungeonMap;
    DungeonManager* dungeonManager;
    PokemonPool* pool;

    int dungeonFloor;
    POINT stairPos;

    std::vector<POINT> wallTiles;

    void EnterDungeonType();

    float elapsedTime;

};

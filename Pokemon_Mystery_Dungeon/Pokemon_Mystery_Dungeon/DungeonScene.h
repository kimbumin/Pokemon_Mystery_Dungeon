#pragma once
#include "Scene.h"
#include "Map.h"

class Player;
class MPlayer;
class Map;

class DungeonScene :public Scene
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
	Map map;
	Image* sampleTile;
	MPlayer* mPlayer;

	int dungeonFloor;
	POINT stairPos;

	TileType tiles[TILE_Y][TILE_X];
	std::vector<POINT> wallTiles;
};


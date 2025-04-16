#include "DungeonScene.h"
#include "Image.h"
#include "CommonFunction.h"


HRESULT DungeonScene::Init()
{
	SetClientRect(g_hWnd, 2000, 1000);


	map.Init();
	wallTiles = map.GetWallTiles(); //wallTilesÁÂÇ¥  Point·Î


	return S_OK;
}

void DungeonScene::Release()
{

}

void DungeonScene::Update()
{

}

void DungeonScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, 2000, 1000, WHITENESS);

	map.Render(hdc);

	//for (const POINT& wall : wallTiles) {
	//	RenderRectAtCenter(hdc, wall.x*TILE_SIZE, wall.y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
	//}
}

#include "DungeonScene.h"
#include "Image.h"
#include "CommonFunction.h"


HRESULT DungeonScene::Init()
{
	SetClientRect(g_hWnd, TILE_SIZE * TILE_X, TILE_SIZE * TILE_Y);

	map.Init();
	wallTiles = map.GetWallTiles(); //wallTilesÁÂÇ¥  Point·Î

	dungeonFloor = 0;

	return S_OK;
}

void DungeonScene::Release()
{

}

void DungeonScene::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6)) {
		//SceneManager::GetInstance()->AddScene("´øÀü¾À", new DungeonScene());
		SceneManager::GetInstance()->ChangeScene("±¤Àå");
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE)) {
		map.Init();
		wallTiles = map.GetWallTiles();
		++dungeonFloor;
	}
}

void DungeonScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, 2000, 2000, BLACKNESS);

	map.Render(hdc);
	map.MiniMapRender(hdc, 0, 0);

	//for (const POINT& wall : wallTiles) {
	//	RenderRectAtCenter(hdc, wall.x*TILE_SIZE, wall.y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
	//}
	
//	map.Draw(hdc);


}

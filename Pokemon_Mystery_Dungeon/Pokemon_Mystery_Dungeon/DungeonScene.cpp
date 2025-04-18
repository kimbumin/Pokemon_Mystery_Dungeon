#include "DungeonScene.h"
#include "Image.h"
#include "CommonFunction.h"


HRESULT DungeonScene::Init()
{
	SetClientRect(g_hWnd, TILE_SIZE * TILE_X, TILE_SIZE * TILE_Y);

	map.Init();
	wallTiles = map.GetWallTiles(); //wallTiles¡¬«•  Point∑Œ


	return S_OK;
}

void DungeonScene::Release()
{

}

void DungeonScene::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6)) {
		//SceneManager::GetInstance()->AddScene("¥¯¿¸æ¿", new DungeonScene());
		SceneManager::GetInstance()->ChangeScene("±§¿Â");
	}

}

void DungeonScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, 2000, 2000, BLACKNESS);

	map.Render(hdc);

	//for (const POINT& wall : wallTiles) {
	//	RenderRectAtCenter(hdc, wall.x*TILE_SIZE, wall.y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
	//}
}

#include "DungeonScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "UIManager.h"


HRESULT DungeonScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	map.Init();
	wallTiles = map.GetWallTiles(); //wallTilesÁÂÇ¥  Point·Î
	CameraManager::GetInstance()->Init(GameViewSize_X, GameViewSize_Y, TILE_X * TILE_SIZE, TILE_Y * TILE_SIZE);

	return S_OK;
}

void DungeonScene::Release()
{

}

void DungeonScene::Update()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	CameraManager::GetInstance()->SetCameraPos(mouse.x, mouse.y);
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6)) {
		//SceneManager::GetInstance()->AddScene("´øÀü¾À", new DungeonScene());
		SceneManager::GetInstance()->ChangeScene("±¤Àå");
	}
}

void DungeonScene::Render(HDC hdc)
{
	RECT cam = CameraManager::GetInstance()->GetViewPos();
	PatBlt(hdc, 0, 0, 2000, 2000, BLACKNESS);

	map.Render(hdc);

	UIManager::GetInstance()->Render(hdc);
	//for (const POINT& wall : wallTiles) {
	//	RenderRectAtCenter(hdc, wall.x*TILE_SIZE, wall.y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
	//}
}

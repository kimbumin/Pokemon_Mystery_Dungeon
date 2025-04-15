#include "CameraTestScene.h"
#include "ImageManager.h"
#include "CameraManager.h"

HRESULT CameraTestScene::Init()
{
	testMap = ImageManager::GetInstance()->AddImage("TestMap", TEXT("Image/SceneImage/Square.bmp"), 954, 714);

	CameraManager::GetInstance()->Init(800, 600);

	return S_OK;
}

void CameraTestScene::Release()
{
}

void CameraTestScene::Update()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);

	CameraManager::GetInstance()->SetCameraPos(mouse.x, mouse.y);
}

void CameraTestScene::Render(HDC hdc)
{
	RECT cam = CameraManager::GetInstance()->GetCameraRect();

	if (testMap)
	{
		BitBlt(
			hdc,
			0,0,
			cam.right - cam.left,
			cam.bottom - cam.top,
			testMap->GetMemDC(),
			cam.left,
			cam.top,
			SRCCOPY
		);
	}
}

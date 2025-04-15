#include "CameraTestScene.h"
#include "ImageManager.h"
#include "CameraManager.h"
#include "UIManager.h"

HRESULT CameraTestScene::Init()
{
	testMap = ImageManager::GetInstance()->AddImage("TestMap", TEXT("Image/SceneImage/Square.bmp"), 954, 714);

	CameraManager::GetInstance()->Init(400, 400);

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

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_TAB))
	{
		//UIManager::GetInstance()->ChangeState(new UIState());
	}

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

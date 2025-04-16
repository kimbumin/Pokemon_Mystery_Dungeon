#include "CameraTestScene.h"
#include "ImageManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "DialogueUIState.h"

HRESULT CameraTestScene::Init()
{
	testMap = ImageManager::GetInstance()->AddImage("TestMap", TEXT("Image/SceneImage/Square.bmp"), 954, 714);

	UIManager::GetInstance()->AddState("DialogueBox", new DialogueUIState());

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
		UIManager::GetInstance()->ChangeState("DialogueBox");
	}

	CameraManager::GetInstance()->SetCameraPos(mouse.x, mouse.y);
	UIManager::GetInstance()->Update();
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
	UIManager::GetInstance()->Render(hdc);
}

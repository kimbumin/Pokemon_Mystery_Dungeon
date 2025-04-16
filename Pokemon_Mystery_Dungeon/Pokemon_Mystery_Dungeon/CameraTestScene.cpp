#include "CameraTestScene.h"
#include "ImageGDIPlusManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "DialogueUIState.h"

HRESULT CameraTestScene::Init()
{
	testMap = ImageGDIPlusManager::GetInstance()->AddImage(
		"TestMap", TEXT("Image/SceneImage/TiniWoods2.bmp"));

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
		testMap->Render(
			hdc,
			-float(cam.left), -float(cam.top),  // 카메라 기준 보정
			0.0f,
			false, false,
			1.0f
		);
	}
	UIManager::GetInstance()->Render(hdc);
}

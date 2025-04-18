#include "CameraTestScene.h"
#include "ImageGDIPlusManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "DialogueUIState.h"

HRESULT CameraTestScene::Init()
{
	testMap = ImageGDIPlusManager::GetInstance()->AddImage(
		"TestMap", TEXT("Image/UIImage/testBackImg.bmp"));

	UIManager::GetInstance()->RegisterAllUIStates();

	CameraManager::GetInstance()->Init(GameViewSize_X, GameViewSize_Y);

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

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_TAB))
	{
		UIManager::GetInstance()->OpenUIStateBox("defaultUI");
	}
	UIManager::GetInstance()->Update();
}

void CameraTestScene::Render(HDC hdc)
{
	RECT cam = CameraManager::GetInstance()->GetViewPos();

	if (testMap)
	{
		testMap->RenderBackground(hdc);
	}
	UIManager::GetInstance()->Render(hdc);
}

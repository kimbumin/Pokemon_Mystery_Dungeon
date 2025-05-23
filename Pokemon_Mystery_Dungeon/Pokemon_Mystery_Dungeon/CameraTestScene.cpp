#include "CameraTestScene.h"

#include "CameraManager.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "DialogueUIState.h"
#include "Image.h"
#include "ImageGDIPlusManager.h"
#include "ImageManager.h"
#include "InfoUIState.h"
#include "UIManager.h"

#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT CameraTestScene::Init()
{
    backGround = ImageManager::GetInstance()->AddImage(
        "SquareBackGround", L"Image/SceneImage/Square3.bmp", SQUARESIZE_X, SQUARESIZE_Y,
        1, 1, 0, RGB(255, 0, 255));
    UIManager::GetInstance()->Init();

    CameraManager::GetInstance()->Init(GameViewSize_X, GameViewSize_Y, 1420,
                                       700);
    UIManager::GetInstance()->AddState("dialogueBox", new DialogueUIState());

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
    // I키 누르면 dialogueBox UI 상태로 전환 + 테스트 대사 출력
    // 흐름
    // CameraTestScene → DialogueManager → UIManager → DialogueUIState →
    // PushDialogueLine()
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x49))  // 'I' 키
    {
        DialogueManager::GetInstance()->ShowLine(
            DialogueTemplate::FoundItem, {{L"itemName", L"Monster Ball"}});
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))  // 'D' 키
    {
        UIManager::GetInstance()->OpenUIStateBox("DungeonUI");
    }

    UIManager::GetInstance()->Update();
}

void CameraTestScene::Render(HDC hdc)
{
    if (backGround)
    {
        backGround->RenderBackground(hdc);
    }
    UIManager::GetInstance()->Render(hdc);
}

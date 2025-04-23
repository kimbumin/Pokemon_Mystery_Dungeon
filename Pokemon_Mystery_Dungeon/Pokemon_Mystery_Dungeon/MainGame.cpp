#include "MainGame.h"

#include "CameraTestScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "PlayerManager.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "SquareScene.h"
#include "TileMapTestScene.h"
#include "TilemapTool.h"
#include "Timer.h"
#include "TurnManager.h"
#include "UIManager.h"
#include "SkillManager.h"
#include "PokemonEvolutionDataLoader.h"
HRESULT MainGame::Init()
{
    ImageManager::GetInstance()->Init();
    KeyManager::GetInstance()->Init();
    SceneManager::GetInstance()->Init();
    UIManager::GetInstance()->Init();
    PokemonDataLoader::GetInstance()->Init();
    PokemonDataLoader::GetInstance()->LoadFromCSV("Data/PokemonBaseStatus.csv");
    PokemonEvolutionDataLoader::GetInstance()->Init();
    PokemonEvolutionDataLoader::GetInstance()->LoadFromCSV(
        "Data/PokemonEvolution.csv");
    
    SkillManager::GetInstance()->LoadSkillsFromCSV("Data/PokemonSkill_English.csv");
    PlayerManager::GetInstance()->Init();
    hdc = GetDC(g_hWnd);

    backBuffer = new Image();
    if (FAILED(backBuffer->Init(TILEMAPTOOL_X, TILEMAPTOOL_Y)))
    {
        MessageBox(g_hWnd, TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
        return E_FAIL;
    }
    //UIManager::GetInstance()->ChangeState("IdleUI");
    SceneManager::GetInstance()->AddScene("Square", new SquareScene);
    SceneManager::GetInstance()->ChangeScene("Square");
    // SceneManager::GetInstance()->AddScene("TestMap", new CameraTestScene());
    // SceneManager::GetInstance()->ChangeScene("TestMap");
    return S_OK;
}

void MainGame::Release()
{
    if (backBuffer)
    {
        backBuffer->Release();
        delete backBuffer;
        backBuffer = nullptr;
    }

    ReleaseDC(g_hWnd, hdc);

    SceneManager::GetInstance()->Release();
    KeyManager::GetInstance()->Release();
    ImageManager::GetInstance()->Release();
    PlayerManager::GetInstance()->Release();
}

void MainGame::Update()
{
    SceneManager::GetInstance()->Update();
    UIManager::GetInstance()->Update();
    InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
    HDC hBackBufferDC = backBuffer->GetMemDC();
    PatBlt(hBackBufferDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

    SceneManager::GetInstance()->Render(hBackBufferDC);

    TimerManager::GetInstance()->Render(hBackBufferDC);

    backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam,
                           LPARAM lParam)
{
    switch (iMessage)
    {
        case WM_KEYDOWN:
            break;
        case WM_LBUTTONDOWN:
            break;
        case WM_LBUTTONUP:
            break;
        case WM_MOUSEMOVE:
            g_ptMouse.x = LOWORD(lParam);
            g_ptMouse.y = HIWORD(lParam);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

#include "DungeonScene.h"

#include "BossScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MPlayer.h"
#include "UIManager.h"
#include "Camera.h"
#include "PokemonPool.h"
#include "TurnManager.h"
#include "DungeonManager.h"
#include "Map.h"
#include "PlayerManager.h"
#include "PokemonPlayer.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "FadeManager.h"
#include "SquareScene.h"

HRESULT DungeonScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    dungeonMap = new Map();
    dungeonMap->Init();

    dungeonManager = new DungeonManager();
    dungeonManager->Init();
    dungeonManager->SetDungeonMap(dungeonMap);
    EnterDungeonType();

    Camera::GetInstance()->SetMapSize({TILE_X * TILE_SIZE, TILE_Y * TILE_SIZE});
    Camera::GetInstance()->SetScreenSize({500, 400});

    wallTiles = dungeonMap->GetWallTiles();  // wallTiles좌표  Point로

    dungeonFloor = 0;
    elapsedTime = 0.f;

    GenerateNextFloor();
    FadeManager::GetInstance()->StartFadeIn();
    return S_OK;
}

void DungeonScene::Release()
{
    if (dungeonManager)
    {
        dungeonManager->ExitDungeon();
        delete dungeonManager;
        dungeonManager = nullptr;
    }
    if (dungeonMap)
    {
        delete dungeonMap;
        dungeonMap = nullptr;
    }

}

void DungeonScene::Update()
{
    if (dungeonMap)
    {
        dungeonMap->Update();
    }
    if (pool)
    {
        pool->Update();
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_TAB))
    {
        UIManager::GetInstance()->OpenUIStateBox("defaultUI");
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x49))  // 'I' 키
    {
        DialogueManager::GetInstance()->ShowLine(
            DialogueTemplate::FoundItem, { {L"itemName", L"Monster Ball"} });
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))  // 'D' 키
    {
        UIManager::GetInstance()->OpenUIStateBox("DungeonUI");

        // SetDugeonType이런 거 만들어 줘야되고,
        // DungeonScene이동,
        //
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x59))  // 'Y' 키
    {
        UIManager::GetInstance()->OpenUIStateBox("YesOrNoUI");
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x4D))  // 'M' 키
    {
        UIManager::GetInstance()->OpenUIStateBox("DownStairUI");
    }

    TurnManager::GetInstance()->Update();

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SceneManager::GetInstance()->ChangeScene("Square");
    }


    if (isSceneTransition && FadeManager::GetInstance()->IsFadeComplete())
    {
        GenerateNextFloor();
        FadeManager::GetInstance()->StartFadeIn(1.0);
        isSceneTransition = false;
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE) &&!FadeManager::GetInstance()->IsFading())
    {
        ++dungeonFloor;
        FadeManager::GetInstance()->StartFadeOut(1.0);
        isSceneTransition = true;
    }
    if (dungeonFloor > 3)
    {
        SceneManager::GetInstance()->ChangeScene("Square");
        dungeonFloor = 0;
    }

    elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
    if (elapsedTime > 0.016f)
    {
        FadeManager::GetInstance()->Update();
        Camera::GetInstance()->Update(elapsedTime);
        elapsedTime = 0;
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F9)){
        Camera::GetInstance()->Shake(0.3f, 10);
    }
}

void DungeonScene::Render(HDC hdc)
{
    HRGN clipRegion = CreateRectRgn(0, 0, 500, 400);
    SelectClipRgn(hdc, clipRegion);


    if (dungeonMap)
    {
        dungeonMap->RenderWithCamera(hdc);
        dungeonMap->MiniMapRender(hdc, 0, 0);
    }
    if (pool)
    {
        pool->Render(hdc);
    }

    SelectClipRgn(hdc, NULL);
    DeleteObject(clipRegion);


    //UI등 clip영역 밖에 추가하실거면 이 밑에 두세요 --
    UIManager::GetInstance()->Render(hdc);
    FadeManager::GetInstance()->Render(hdc, 500, 400);
}

void DungeonScene::GenerateNextFloor()
{
    dungeonManager->ExitDungeon();
    dungeonMap->Init();
    EnterDungeonType();
    wallTiles = dungeonMap->GetWallTiles();
    stairPos = ConvertToPixel(dungeonMap->GetStairPos());
}

POINT DungeonScene::ConvertToPixel(POINT tilePos)
{
    tilePos.x *= TILE_SIZE;
    tilePos.y *= TILE_SIZE;
    return tilePos;
}

bool DungeonScene::IsPlayerOnStair()
{
    FPOINT playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
    return abs(playerPos.x - stairPos.x) <= TILE_SIZE &&
           abs(playerPos.y - stairPos.y) <= TILE_SIZE;
}

void DungeonScene::EnterDungeonType()
{
    if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_FOREST)
    {
        dungeonManager->EnterDungeon("TinyForest");

    }
    else if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_ICE)
    {
        dungeonManager->EnterDungeon("IceCave");

    }
    else if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_MAGMA)
    {
        dungeonManager->EnterDungeon("Volcano");
    }
    UIManager::GetInstance()->ChangeState("IdleUI");

    pool = dungeonManager->GetPokemonPool();
    TurnManager::GetInstance()->InitTurnOrder(pool);

}

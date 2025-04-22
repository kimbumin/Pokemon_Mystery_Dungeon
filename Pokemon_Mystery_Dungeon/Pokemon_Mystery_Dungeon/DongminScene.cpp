#include "DongminScene.h"

#include "DungeonManager.h"
#include "Map.h"
#include "PokemonPool.h"
#include "TurnManager.h"
HRESULT DongminScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    dungeonMap = new Map();
    dungeonMap->Init();
    dungeonManager = new DungeonManager();
    dungeonManager->Init();
    dungeonManager->SetDungeonMap(dungeonMap);
    dungeonManager->EnterDungeon("TinyForest");

    pool = dungeonManager->GetPokemonPool();
    TurnManager::GetInstance()->InitTurnOrder(pool);

    return S_OK;
}

void DongminScene::Release()
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

void DongminScene::Update()
{
    if (dungeonMap)
    {
        dungeonMap->Update();
    }
    if (pool)
    {
        pool->Update();
    }
    TurnManager::GetInstance()->Update();
}

void DongminScene::Render(HDC hdc)
{
    if (dungeonMap)
    {
        dungeonMap->Render(hdc);
    }
    if (pool)
    {
        pool->Render(hdc);
    }
}
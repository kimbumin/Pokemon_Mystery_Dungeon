#include "BuminScene.h"

#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "DungeonManager.h"
#include "Map.h"
#include "PokemonPool.h"
#include "TurnManager.h"
#include "UIManager.h"
#include "BattleSystem.h"
#include "SkillManager.h"

HRESULT BuminScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    dungeonMap = new Map();
    dungeonMap->Init();
    dungeonManager = new DungeonManager();
    dungeonManager->Init();
    dungeonManager->SetDungeonMap(dungeonMap);
    dungeonManager->EnterDungeon("TinyForest");

    UIManager::GetInstance()->ChangeState("IdleUI");

    pool = dungeonManager->GetPokemonPool();
    TurnManager::GetInstance()->InitTurnOrder(pool);

    BattleSystem::GetInstance()->SetPokemonPool(pool);
    SkillManager::GetInstance()->LoadSkillsFromCSV("Data/PokemonSkill_English.csv");

    return S_OK;
}

void BuminScene::Release()
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

void BuminScene::Update()
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
            DialogueTemplate::FoundItem, {{L"itemName", L"Monster Ball"}});
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
}

void BuminScene::Render(HDC hdc)
{
    if (dungeonMap)
    {
        dungeonMap->Render(hdc);
    }
    if (pool)
    {
        pool->Render(hdc);
    }
    UIManager::GetInstance()->Render(hdc);
}
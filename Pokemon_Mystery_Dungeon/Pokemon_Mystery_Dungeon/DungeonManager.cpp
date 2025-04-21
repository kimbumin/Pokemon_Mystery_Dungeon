#include "DungeonManager.h"
#include "PokemonBuilder.h"
#include "PokemonPool.h"
#include "PokemonImageLoader.h"
#include "TurnManager.h"
#include "CommonFunction.h"

void DungeonManager::Init()
{
    LoadDungeonData();
}

void DungeonManager::LoadDungeonData()
{
    // 던전 이름 → 등장 포켓몬 ID + 레벨 범위 + 수
    // 외부 파일로 빼낼생각이 있다
    // 밑에는 예시
    dungeonSpawnMap["Volcano"] = DungeonSpawnInfo{
        {4, 5, 37},
        5, 10,
        10
    };

    dungeonSpawnMap["TinyForest"] = DungeonSpawnInfo{
        {10, 13, 16},
        3, 6,
        8
    };

}

void DungeonManager::EnterDungeon(string dungeonName)
{
    pool = new PokemonPool();
    pool->Init();

    builder = new PokemonBuilder();
    builder->SetPool(pool);

    if (dungeonSpawnMap.find(dungeonName) == dungeonSpawnMap.end()) 
    {
        return;
    }

    DungeonSpawnInfo& info = dungeonSpawnMap[dungeonName];

    // 이미지 선등록
    for (int id : info.pokemonIds)
    {
        PokemonImageLoader::GetInstance()->LoadPokemonAnim(id);
    }

    // 적 스폰
    for (int i = 0; i < info.spawnCount; ++i)
    {
        PokemonBase* enemy = builder->BuildFromDungeonInfo(info);
    }

    // 턴 매니저한테 Pool 넘기기
    TurnManager::GetInstance()->InitTurnOrder(pool);
}
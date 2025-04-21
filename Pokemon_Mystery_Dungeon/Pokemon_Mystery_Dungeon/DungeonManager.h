#pragma once
#include "config.h"

class PokemonBuilder;
class PokemonPool;

class DungeonManager
{
private:
    // 던전 이름, 던전 정보
    unordered_map<string, DungeonSpawnInfo> dungeonSpawnMap;
    
    PokemonBuilder* builder;
    PokemonPool* pool;

public:
    void Init();
    void LoadDungeonData();
    void EnterDungeon(string dungeonName);
    void ExitDungeon();

    DungeonManager() {};
    virtual ~DungeonManager() {};
};
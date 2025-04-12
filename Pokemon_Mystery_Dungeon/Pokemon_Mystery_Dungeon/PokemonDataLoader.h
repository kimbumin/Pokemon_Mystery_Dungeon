#pragma once
#include "Singleton.h"
#include "config.h"

class PokemonDataLoader : public Singleton<PokemonDataLoader>
{
private:
    unordered_map<int, PokemonData> baseDataMap;

public:
    void Init();
    bool LoadFromCSV(string& filepath);

    // Getter
    PokemonData* GetData(int idNumber);
    unordered_map<int, PokemonData>& GetAllData();
};
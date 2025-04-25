#pragma once
#include "config.h"
#include "Singleton.h"

class PokemonEvolutionDataLoader : public Singleton<PokemonEvolutionDataLoader>
{
private:
    unordered_map<int, EvolutionData> evolutionMap;

public:
    void Init();
    void Release();

    bool LoadFromCSV(const string& filePath);

    // Getter
    EvolutionData* GetData(int idNumber);
    unordered_map<int, EvolutionData>& GetAllData();
};

#include "PokemonDataLoader.h"
#include <fstream>
#include <sstream>


void PokemonDataLoader::Init()
{
    baseDataMap.clear();
}

void PokemonDataLoader::Release()
{
    PokemonDataLoader::GetInstance()->ReleaseInstance();
}

bool PokemonDataLoader::LoadFromCSV(const string& filepath)
{
    ifstream file(filepath);
    if (!file.is_open()) return false;

    string line;
    getline(file, line); // 첫 줄 생략

    while (getline(file, line)) 
    {
        stringstream stream(line);
        string token;

        PokemonData data;

        getline(stream, token, ',');
        data.idNumber = stoi(token);
        getline(stream, data.name, ',');

        // 능력치들
        getline(stream, token, ',');
        data.hp = std::stoi(token);
        getline(stream, token, ',');
        data.atk = std::stoi(token);
        getline(stream, token, ',');
        data.def = std::stoi(token);
        getline(stream, token, ',');
        data.spAtk = std::stoi(token);
        getline(stream, token, ',');
        data.spDef = std::stoi(token);
        getline(stream, token, ',');
        data.speed = std::stoi(token);
        getline(stream, token, ',');
        data.sum = std::stoi(token);
        getline(stream, token, ',');
        data.average = std::stof(token);

        // 타입1, 타입2
        getline(stream, token, ',');
        if (!token.empty()) data.types.push_back(token);
        getline(stream, token, ',');
        if (!token.empty()) data.types.push_back(token);

        baseDataMap[data.idNumber] = data;
    }

    return true;
}

PokemonData* PokemonDataLoader::GetData(int idNumber)
{
    auto iter = baseDataMap.find(idNumber);
    return (iter != baseDataMap.end()) ? &iter->second : nullptr;
}

unordered_map<int, PokemonData>& PokemonDataLoader::GetAllData()
{
    return baseDataMap;
}

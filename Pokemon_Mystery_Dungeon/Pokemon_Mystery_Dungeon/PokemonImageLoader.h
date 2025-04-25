#pragma once
// clang-format off
#include "config.h"
// clang-format on
#include "Singleton.h"

class PokemonImageLoader : public Singleton<PokemonImageLoader>
{
private:
    unordered_set<string> loadedImageKeys;

public:
    void Release();
    void LoadPokemonAnim(int pokemonId);
    void ClearPokemonImage();

    string PokemonIdToString(int pokemonId);
};

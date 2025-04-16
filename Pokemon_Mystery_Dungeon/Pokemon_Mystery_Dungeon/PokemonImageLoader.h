#pragma once
#include "config.h"
#include "Singleton.h"

class PokemonImageLoader : public Singleton<PokemonImageLoader>
{
private:
	unordered_set<string> loadedImageKeys;

public:
	void LoadPokemonAnim(int pokemonId);
	void ClearPokemonImage();

	string PokemonIdToString(int pokemonId);
};


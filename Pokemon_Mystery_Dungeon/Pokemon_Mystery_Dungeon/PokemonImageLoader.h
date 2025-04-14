#pragma once
#include "config.h"
#include "Singleton.h"

class PokemonImageLoader : public Singleton<PokemonImageLoader>
{
private:
	unordered_set<string> loadedImageKeys;

public:
	void BeginDungeon(const string& dungeonName);
	void LoadPokemonAnim(int pokemonId);
	void EndDungeon();

	string PokemonIdToString(int pokemonId);
};


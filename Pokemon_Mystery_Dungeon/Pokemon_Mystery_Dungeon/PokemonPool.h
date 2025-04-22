#pragma once
#include "config.h"

class PokemonBase;
class PokemonPool
{
private:
    vector<PokemonBase*> pokemonPool;
    vector<PokemonBase*>::iterator iterPokemonPool;

protected:
public:
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render(HDC hdc);

    PokemonBase* Get();
    void Return(PokemonBase* pokemon);
    void ReturnEnemies();

    bool IsEmpty();

    vector<PokemonBase*>::iterator begin()
    {
        return pokemonPool.begin();
    }
    vector<PokemonBase*>::iterator end()
    {
        return pokemonPool.end();
    }

    PokemonPool() {};
    virtual ~PokemonPool() {};
};
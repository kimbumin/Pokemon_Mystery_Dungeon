#pragma once
// clang-format off
#include "config.h"
// clang-format on
#include <functional>

class ISkill;
class PokemonBase;
class PokemonPool
{
private:
    struct RenderItem {
        float y;
        void* object;                 // 포인터 (PokemonBase* or ISkill*)
        bool isSkill;                 // true면 ISkill, false면 PokemonBase
        std::shared_ptr<ISkill> skillRef;  // isSkill일 때만 참조 보관 (수명 관리용)
    };


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
    bool IsPositionBlocked(FPOINT pos);

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
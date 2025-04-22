#pragma once
#include "PokemonBase.h"

class PokemonEnemy : public PokemonBase
{
private:
protected:
public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void ExecuteTurn();

    PokemonEnemy() {};
    virtual ~PokemonEnemy() {};
};

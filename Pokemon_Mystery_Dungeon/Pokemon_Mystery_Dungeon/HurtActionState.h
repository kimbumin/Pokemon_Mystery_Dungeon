#pragma once
#include "IActionState.h"

class HurtActionState : public IActionState
{
private:
    bool isFinished;

    float duration;
    float elapsed;

public:
    virtual void Enter(PokemonBase* owner);
    virtual void Update(PokemonBase* owner);
    virtual void Exit(PokemonBase* owner);
    virtual bool IsFinished();
    virtual bool CanOverride();

    HurtActionState();
    virtual ~HurtActionState() {};
};

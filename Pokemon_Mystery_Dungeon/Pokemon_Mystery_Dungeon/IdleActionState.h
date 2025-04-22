#pragma once
#include "IActionState.h"

class IdleActionState : public IActionState
{
private:
    bool isFinished;

public:
    virtual void Enter(PokemonBase* owner);
    virtual void Update(PokemonBase* owner);
    virtual void Exit(PokemonBase* owner);
    virtual bool IsFinished();
    virtual bool CanOverride();

    IdleActionState();
    virtual ~IdleActionState() {};
};

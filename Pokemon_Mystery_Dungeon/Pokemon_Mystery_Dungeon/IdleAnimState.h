#pragma once
#include "IAnimState.h"

class IdleAnimState : public IAnimState
{
private:
    bool isFinished;

public:
    virtual void Enter(PokemonBase* owner) override;
    virtual void Update(PokemonBase* owner) override;
    virtual void Exit(PokemonBase* owner) override;
    virtual bool IsFinished() override;
    virtual bool CanOverride() override;

    IdleAnimState();
    virtual ~IdleAnimState() {};
};

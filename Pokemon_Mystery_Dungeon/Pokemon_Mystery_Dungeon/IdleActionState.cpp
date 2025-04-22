#include "IdleActionState.h"

#include "PokemonBase.h"

void IdleActionState::Enter(PokemonBase* owner)
{
    isFinished = false;
    owner->PlayIdleAnim();
}

void IdleActionState::Update(PokemonBase* owner)
{
}

void IdleActionState::Exit(PokemonBase* owner)
{
}

bool IdleActionState::IsFinished()
{
    return isFinished;
}

bool IdleActionState::CanOverride()
{
    return true;
}

IdleActionState::IdleActionState()
{
    isFinished = false;
}

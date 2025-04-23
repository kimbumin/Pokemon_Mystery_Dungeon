#include "IdleActionState.h"

#include "PokemonBase.h"

void IdleActionState::Enter(PokemonBase* owner)
{
    isFinished = false;
    elapsed = 0.f;
    duration - 1.f;
    owner->PlayIdleAnim();
}

void IdleActionState::Update(PokemonBase* owner)
{
    if (isFinished)
    {
        return;
    }

    elapsed += TimerManager::GetInstance()->GetDeltaTime();

    if (elapsed >= duration)
    {
        isFinished = true;
        return;
    }
}

void IdleActionState::Exit(PokemonBase* owner)
{
}

bool IdleActionState::IsFinished()
{
    return true;
}

bool IdleActionState::CanOverride()
{
    return true;
}

IdleActionState::IdleActionState()
{
    isFinished = false;
}

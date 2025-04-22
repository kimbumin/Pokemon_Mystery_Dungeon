#include "WalkAnimState.h"

#include "PokemonAnimator.h"
#include "PokemonBase.h"
void WalkAnimState::Enter(PokemonBase* owner)
{
    isFinished = false;
    owner->GetAnimator()->Play("Walk", owner->GetDirection());
}

void WalkAnimState::Update(PokemonBase* owner)
{
    owner->GetAnimator()->Update();
    if (owner->GetAnimator()->IsFinished("Walk"))
    {
        isFinished = true;
    }
}

void WalkAnimState::Exit(PokemonBase* owner)
{
}

bool WalkAnimState::IsFinished()
{
    return isFinished;
}

bool WalkAnimState::CanOverride()
{
    return isFinished;
}

WalkAnimState::WalkAnimState()
{
    isFinished = false;
}

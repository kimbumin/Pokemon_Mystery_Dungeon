#include "RotateAnimState.h"

#include "PokemonAnimator.h"
#include "PokemonBase.h"

void RotateAnimState::Enter(PokemonBase* owner)
{
    isFinished = false;
    owner->GetAnimator()->Play("Rotate", owner->GetDirection());
}

void RotateAnimState::Update(PokemonBase* owner)
{
    owner->GetAnimator()->Update();
    if (owner->GetAnimator()->IsFinished("Rotate"))
    {
        isFinished = true;
    }
}

void RotateAnimState::Exit(PokemonBase* owner)
{
}

bool RotateAnimState::IsFinished()
{
    return isFinished;
}

bool RotateAnimState::CanOverride()
{
    return isFinished;
}

RotateAnimState::RotateAnimState()
{
    isFinished = false;
}

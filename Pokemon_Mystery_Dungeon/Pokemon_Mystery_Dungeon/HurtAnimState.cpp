#include "HurtAnimState.h"

#include "PokemonAnimator.h"
#include "PokemonBase.h"

void HurtAnimState::Enter(PokemonBase* owner)
{
    isFinished = false;
    owner->GetAnimator()->Play("Hurt", owner->GetDirection());
}

void HurtAnimState::Update(PokemonBase* owner)
{
    owner->GetAnimator()->Update();
    if (owner->GetAnimator()->IsFinished("Hurt"))
    {
        isFinished = true;
    }
}

void HurtAnimState::Exit(PokemonBase* owner)
{
}

bool HurtAnimState::IsFinished()
{
    return isFinished;
}

bool HurtAnimState::CanOverride()
{
    return isFinished;
}

HurtAnimState::HurtAnimState()
{
    isFinished = false;
}

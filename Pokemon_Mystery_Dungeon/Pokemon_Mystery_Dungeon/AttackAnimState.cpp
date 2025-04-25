#include "AttackAnimState.h"

#include "PokemonAnimator.h"
#include "PokemonBase.h"

void AttackAnimState::Enter(PokemonBase* owner)
{
    isFinished = false;
    owner->GetAnimator()->Play("Attack", owner->GetDirection());
}

void AttackAnimState::Update(PokemonBase* owner)
{
    owner->GetAnimator()->Update();

    if (owner->GetAnimator()->IsFinished("Attack"))
    {
        isFinished = true;
    }
}

void AttackAnimState::Exit(PokemonBase* owner)
{
}

bool AttackAnimState::IsFinished()
{
    return isFinished;
}

bool AttackAnimState::CanOverride()
{
    return isFinished;
}

AttackAnimState::AttackAnimState()
{
    isFinished = false;
}

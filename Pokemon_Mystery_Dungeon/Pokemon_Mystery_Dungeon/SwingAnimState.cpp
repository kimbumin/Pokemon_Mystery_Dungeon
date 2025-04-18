#include "SwingAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"

void SwingAnimState::Enter(PokemonBase* owner)
{
    isFinished = false;
    owner->GetAnimator()->Play("Swing", owner->GetDirection());
}

void SwingAnimState::Update(PokemonBase* owner)
{
    owner->GetAnimator()->Update();
    if (owner->GetAnimator()->IsFinished("Swing"))
    {
        isFinished = true;
    }
}

void SwingAnimState::Exit(PokemonBase* owner)
{
}

bool SwingAnimState::IsFinished()
{
    return isFinished;
}

bool SwingAnimState::CanOverride()
{
    return isFinished;
}

SwingAnimState::SwingAnimState()
{
    isFinished = false;
}

#include "SwingAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"

void SwingAnimState::Enter(PokemonBase* outer)
{
    finished = false;
    outer->GetAnimator()->Play("Swing", outer->GetDirection());
}

void SwingAnimState::Update(PokemonBase* outer)
{
    outer->GetAnimator()->Update();
    if (outer->GetAnimator()->IsFinished("Swing"))
    {
        finished = true;
    }
}

void SwingAnimState::Exit(PokemonBase* outer)
{
}

bool SwingAnimState::IsFinished()
{
    return finished;
}

bool SwingAnimState::CanOverride()
{
    return finished;
}

SwingAnimState::SwingAnimState()
{
    finished = false;
}

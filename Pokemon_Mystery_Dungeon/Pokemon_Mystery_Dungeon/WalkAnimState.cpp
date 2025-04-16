#include "WalkAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"
void WalkAnimState::Enter(PokemonBase* outer)
{
	finished = false;
	outer->GetAnimator()->Play("Walk", outer->GetDirection());
}

void WalkAnimState::Update(PokemonBase* outer)
{
	outer->GetAnimator()->Update();
	if (outer->GetAnimator()->IsFinished("Walk"))
	{
		finished = true;
	}
}

void WalkAnimState::Exit(PokemonBase* outer)
{
}

bool WalkAnimState::IsFinished()
{
	return finished;
}

bool WalkAnimState::CanOverride()
{
	return finished;
}

WalkAnimState::WalkAnimState()
{
	finished = false;
}

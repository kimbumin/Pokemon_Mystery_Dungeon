#include "RotateAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"

void RotateAnimState::Enter(PokemonBase* outer)
{
	finished = false;
	outer->GetAnimator()->Play("Rotate", outer->GetDirection());
}

void RotateAnimState::Update(PokemonBase* outer)
{
	outer->GetAnimator()->Update();
	if (outer->GetAnimator()->IsFinished("Rotate"))
	{
		finished = true;
	}
}

void RotateAnimState::Exit(PokemonBase* outer)
{
}

bool RotateAnimState::IsFinished()
{
	return finished;
}

bool RotateAnimState::CanOverride()
{
	return finished;
}

RotateAnimState::RotateAnimState()
{
	finished = false;

}

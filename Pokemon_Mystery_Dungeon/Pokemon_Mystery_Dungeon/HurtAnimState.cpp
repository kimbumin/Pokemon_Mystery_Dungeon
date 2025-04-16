#include "HurtAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"

void HurtAnimState::Enter(PokemonBase* outer)
{
	finished = false;
	outer->GetAnimator()->Play("Hurt", outer->GetDirection());
}

void HurtAnimState::Update(PokemonBase* outer)
{
	outer->GetAnimator()->Update();
	if (outer->GetAnimator()->IsFinished("Hurt"))
	{
		finished = true;
	}
}

void HurtAnimState::Exit(PokemonBase* outer)
{
}

bool HurtAnimState::IsFinished()
{
	return finished;
}

bool HurtAnimState::CanOverride()
{
	return finished;
}

HurtAnimState::HurtAnimState()
{
	finished = false;
}


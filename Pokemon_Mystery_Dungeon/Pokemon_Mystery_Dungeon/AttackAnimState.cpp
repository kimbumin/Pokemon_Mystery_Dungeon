#include "AttackAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"

void AttackAnimState::Enter(PokemonBase* outer)
{
	finished = false;
	outer->GetAnimator()->Play("Attack", outer->GetDirection());
}

void AttackAnimState::Update(PokemonBase* outer)
{
	outer->GetAnimator()->Update();

	if (outer->GetAnimator()->IsFinished("Attack"))
	{
		finished = true;
	}
}

void AttackAnimState::Exit(PokemonBase* outer)
{

}

bool AttackAnimState::IsFinished()
{
	return finished;
}

bool AttackAnimState::CanOverride()
{
	return finished;
}

AttackAnimState::AttackAnimState()
{
	finished = false;
}

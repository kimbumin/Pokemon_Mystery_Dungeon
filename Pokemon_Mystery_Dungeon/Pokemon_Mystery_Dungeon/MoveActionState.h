#pragma once
#include "IActionState.h"

class MoveActionState : public IActionState
{
private:
	bool isFinished;
	FPOINT startPos;
	FPOINT destPos;
	FPOINT currentPos;
	Direction direction;
	float duration;
	float elapsed;

public:
	virtual void Enter(PokemonBase* owner);
	virtual void Update(PokemonBase* owner);
	virtual void Exit(PokemonBase* owner);
	virtual bool IsFinished();
	virtual bool CanOverride();

	float Lerp(float a, float b, float t);

	MoveActionState();
	virtual ~MoveActionState() {};
};


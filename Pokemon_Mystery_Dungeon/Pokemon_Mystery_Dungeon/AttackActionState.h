#pragma once
#include "IActionState.h"

class ISkill;
class AttackActionState : public IActionState
{
private:
    bool isFinished;

    Direction direction;

    shared_ptr<ISkill> selectedSkill;

    float duration;
    float elapsed;

public:
    virtual void Enter(PokemonBase* owner);
    virtual void Update(PokemonBase* owner);
    virtual void Exit(PokemonBase* owner);
    virtual bool IsFinished();
    virtual bool CanOverride();

    void SelectSkill(shared_ptr<ISkill> newSkill);

    AttackActionState();
    virtual ~AttackActionState() {};
};

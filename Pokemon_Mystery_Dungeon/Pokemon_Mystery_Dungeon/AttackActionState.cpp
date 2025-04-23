#include "AttackActionState.h"

#include "ISkill.h"
#include "PokemonBase.h"

void AttackActionState::Enter(PokemonBase* owner)
{
    isFinished = false;

    direction = owner->GetDirection();

    // Check 이거 함수화 할 필요 있어보임. 조금 길다
    if (selectedSkill->GetAnimType() == "Rotate")
    {
        owner->PlayRotateAnim();
    }
    else if (selectedSkill->GetAnimType() == "Attack")
    {
        owner->PlayAttackAnim();
    }
    else
    {
        owner->PlaySwingAnim();
    }

    selectedSkill->Use(owner);
    duration = 1.f;
    // Check 애니메이션 총 재생 시간 -> 하드코딩 말고 다른 방법 개선 필요
    // (PokemonBase에서도 AddAnimation 할때 하드 코딩 되어있음)
    elapsed = 0.f;

    /*   selectedSkill->Use();*/
}

void AttackActionState::Update(PokemonBase* owner)
{
    if (isFinished)
    {
        return;
    }
    if (selectedSkill)
    {
        selectedSkill->Update();
    }
    elapsed += TimerManager::GetInstance()->GetDeltaTime();

    if (elapsed >= duration)
    {
        isFinished = true;
        return;
    }
}

void AttackActionState::Exit(PokemonBase* owner)
{
}

bool AttackActionState::IsFinished()
{
    return isFinished;
}

bool AttackActionState::CanOverride()
{
    return isFinished;
}

void AttackActionState::SelectSkill(shared_ptr<ISkill> newSkill)
{
    selectedSkill = newSkill;
}

AttackActionState::AttackActionState()
{
    isFinished = false;
    selectedSkill = nullptr;
}

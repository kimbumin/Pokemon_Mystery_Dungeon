#include "HurtActionState.h"

#include "PokemonBase.h"

void HurtActionState::Enter(PokemonBase* owner)
{
    isFinished = false;

    duration = 1.f;
    // Check 애니메이션 총 재생 시간 -> 하드코딩 말고 다른 방법 개선 필요
    // (PokemonBase에서도 AddAnimation 할때 하드 코딩 되어있음)
    elapsed = 0.f;

    owner->PlayHurtAnim();
}

void HurtActionState::Update(PokemonBase* owner)
{
    elapsed += TimerManager::GetInstance()->GetDeltaTime();

    if (elapsed >= duration)
    {
        isFinished = true;
        return;
    }
    if (owner->GetCurrentPokemonData().hp >= 0)
    {
        // 여기는 전투시스템 만들면 해야하나 생각
    }
}

void HurtActionState::Exit(PokemonBase* owner)
{
}

bool HurtActionState::IsFinished()
{
    return isFinished;
}

bool HurtActionState::CanOverride()
{
    return isFinished;
}

HurtActionState::HurtActionState()
{
    isFinished = false;
}

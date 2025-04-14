#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "Image.h"
#include "PokemonAnimator.h"
#include "IAnimState.h"
#include "IdleAnimState.h"
#include "AttackAnimState.h"

HRESULT PokemonBase::Init()
{
    baseStatus = PokemonDataLoader::GetInstance()->GetData(6);
    currentStatus = *baseStatus;
    level = 5; // 시작 레벨
    CalStatus();
    currentHp = currentStatus.hp;
    animator = new PokemonAnimator();

    currentAnimState = nullptr;

    SetAnimState(new IdleAnimState());

    string idStr = PokemonImageLoader::GetInstance()->PokemonIdToString(baseStatus->idNumber);
    for (auto type = animTypes.begin(); type != animTypes.end(); ++type)
    {
        string key = idStr + *type;
        Image* image = ImageManager::GetInstance()->FindImage(key);
        if (image) {
            int frameX = image->GetMaxFrameX();
            int frameY = image->GetMaxFrameY();
            float frameTime = 0.1f;
            animator->AddAnimation(*type, image, frameX, frameY, frameTime, *type == "Idle");
        }
    }
    return S_OK;
}

void PokemonBase::Release()
{
    if (animator)
    {
        animator->Release();
        delete animator;
        animator = nullptr;
    }

}

void PokemonBase::Update()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F2)) 
    {
        SetAnimState(new AttackAnimState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F3))
    {
        SetAnimState(new IdleAnimState());
    }
    if (currentAnimState && currentAnimState->IsFinished())
    {
        SetAnimState(new IdleAnimState());
    }
    if (currentAnimState)
    {
        currentAnimState->Update(this);
    }
}

void PokemonBase::Render(HDC hdc)
{
    animator->Render(hdc, pos.x, pos.y);
}

void PokemonBase::CalStatus()
{
    currentStatus.hp = CalStat(baseStatus->hp) + 10/*보정값*/;
    currentStatus.atk = CalStat(baseStatus->atk) + 5/*보정값*/;
    currentStatus.def = CalStat(baseStatus->def) + 5/*보정값*/;
    currentStatus.spAtk = CalStat(baseStatus->spAtk) + 5/*보정값*/;
    currentStatus.spDef = CalStat(baseStatus->spDef) + 5/*보정값*/;
    currentStatus.speed = CalStat(baseStatus->speed) + 5/*보정값*/;
}

int PokemonBase::CalStat(int value)
{
    return (value + IV + EV + 100) * level / 100;
}

void PokemonBase::SetAnimState(IAnimState* newState)
{
    if (currentAnimState)
    {
        currentAnimState->Exit(this);
    }
    currentAnimState = newState;
    if (currentAnimState)
    {
        currentAnimState->Enter(this);
    }
}

#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "Image.h"
#include "PokemonAnimator.h"
#include "IAnimState.h"
#include "IdleAnimState.h"
#include "AttackAnimState.h"
#include "WalkAnimState.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
#include "HurtAnimState.h"

HRESULT PokemonBase::Init()
{
    isAlive = true;
    baseStatus = PokemonDataLoader::GetInstance()->GetData(1); // 따로 빌더에서 정해줄 것

    currentStatus = *baseStatus;
    level = 5; // 따로 빌더에서 정해줄 것
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
        if (image) 
        {
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
        SetAnimState(new IdleAnimState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F3))
    {
        SetAnimState(new AttackAnimState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F4))
    {
        SetAnimState(new WalkAnimState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F5))
    {
        SetAnimState(new RotateAnimState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SetAnimState(new SwingAnimState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F7))
    {
        SetAnimState(new HurtAnimState());
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
    if (currentAnimState && !currentAnimState->CanOverride()) 
    {
        delete newState;
        return;
    }

    if (currentAnimState)
    {
        currentAnimState->Exit(this);
        delete currentAnimState;
    }
    currentAnimState = newState;
    if (currentAnimState)
    {
        currentAnimState->Enter(this);
    }
}

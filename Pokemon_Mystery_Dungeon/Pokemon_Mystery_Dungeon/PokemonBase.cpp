#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "Image.h"
#include "PokemonAnimator.h"
#include "IdleAnimState.h"
#include "AttackAnimState.h"
#include "WalkAnimState.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
#include "HurtAnimState.h"

#include "MoveActionState.h"
#include "IdleActionState.h"
// Skill
// UseItem
HRESULT PokemonBase::Init()
{
    isAlive = true;
    baseStatus = PokemonDataLoader::GetInstance()->GetData(151); // 따로 빌더에서 정해줄 것

    currentStatus = *baseStatus;
    level = 5; // 따로 빌더에서 정해줄 것
    CalStatus();
    currentHp = currentStatus.hp;
    animator = new PokemonAnimator();

    currentAnimState = nullptr;
    currentActionState = nullptr;

    SetAnimState(new IdleAnimState());
    SetActionState(new IdleActionState());

    string idStr = PokemonImageLoader::GetInstance()->PokemonIdToString(baseStatus->idNumber);
    for (auto type = animTypes.begin(); type != animTypes.end(); ++type)
    {
        string key = idStr + *type;
        Image* image = ImageManager::GetInstance()->FindImage(key);
        if (image) 
        {
            int frameX = image->GetMaxFrameX();
            int frameY = image->GetMaxFrameY();
            float frameTime = 1.f / frameX;
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

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
    {
        direction = Direction::NORTH;
        SetAnimState(new WalkAnimState());
        SetActionState(new MoveActionState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LEFT))
    {
        direction = Direction::WEST;
        SetAnimState(new WalkAnimState());
        SetActionState(new MoveActionState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
    {
        direction = Direction::SOUTH;
        SetAnimState(new WalkAnimState());
        SetActionState(new MoveActionState());
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RIGHT))
    {
        direction = Direction::EAST;
        SetAnimState(new WalkAnimState());
        SetActionState(new MoveActionState());
    }

    if (currentAnimState && currentAnimState->IsFinished())
    {
        SetAnimState(new IdleAnimState());
    }
    if (currentAnimState)
    {
        currentAnimState->Update(this);
    }    

    if (currentActionState && currentActionState->IsFinished())
    {
        SetActionState(nullptr);
    }
    if (currentActionState)
    {
        currentActionState->Update(this);
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

void PokemonBase::SetActionState(IActionState* newState)
{
    if (currentActionState && !currentActionState->CanOverride())
    {
        delete newState;
        return;
    }

    if (currentActionState)
    {
        currentActionState->Exit(this);
        delete currentActionState;
    }
    currentActionState = newState;
    if (currentActionState)
    {
        currentActionState->Enter(this);
    }
}

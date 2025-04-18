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

    walkAnim = new WalkAnimState;
    idleAnim = new IdleAnimState;
    attackAnim = new AttackAnimState;
    hurtAnim = new HurtAnimState;
    swingAnim = new SwingAnimState;
    rotateAnim = new RotateAnimState;

    //currentAnimState = &idleAnim;
    currentAnimState = nullptr;
    currentActionState = nullptr;

    SetAnimState(idleAnim);
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
            float frameTime = 1.f / frameX; //  Check: 재생 속도 하드코딩 개선 사항
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
    if (walkAnim)
    {
        delete walkAnim;
        walkAnim = nullptr;
    }
    if (idleAnim)
    {
        delete idleAnim;
        idleAnim = nullptr;
    }   
    if (attackAnim)
    {
        delete attackAnim;
        attackAnim = nullptr;
    }   
    if (hurtAnim)
    {
        delete hurtAnim;
        hurtAnim = nullptr;
    }   
    if (swingAnim)
    {
        delete swingAnim;
        swingAnim = nullptr;
    }   
    if (rotateAnim)
    {
        delete rotateAnim;
        rotateAnim = nullptr;
    }
}

void PokemonBase::Update()
{
    if (currentAnimState->CanOverride())
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
        {
            direction = Direction::NORTH;
            //SetAnimState(&walkAnim);
            SetAnimState(walkAnim);
            SetActionState(new MoveActionState());
        }
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LEFT))
        {
            direction = Direction::WEST;
            //SetAnimState(&walkAnim);
            SetAnimState(walkAnim);
            SetActionState(new MoveActionState());
        }
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
        {
            direction = Direction::SOUTH;
            //SetAnimState(&walkAnim);
            SetAnimState(walkAnim);
            SetActionState(new MoveActionState());
        }
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RIGHT))
        {
            direction = Direction::EAST;
            //SetAnimState(&walkAnim);
            SetAnimState(walkAnim);
            SetActionState(new MoveActionState());
        }
    }

    if (currentAnimState && currentAnimState->IsFinished())
    {
        //SetAnimState(&idleAnim);
        SetAnimState(idleAnim);
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
        return;
    }
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

void PokemonBase::PlayWalkAnim() 
{ 
   // SetAnimState(&walkAnim); 
    SetAnimState(walkAnim); 
}
void PokemonBase::PlayIdleAnim() 
{ 
    //SetAnimState(&idleAnim); 
    SetAnimState(idleAnim); 
}
void PokemonBase::PlayAttackAnim() 
{ 
    //SetAnimState(&attackAnim); 
    SetAnimState(attackAnim); 
}
void PokemonBase::PlayHurtAnim() 
{ 
   // SetAnimState(&hurtAnim); 
    SetAnimState(hurtAnim); 
}
void PokemonBase::PlaySwingAnim() 
{ 
    //SetAnimState(&swingAnim); 
    SetAnimState(swingAnim); 
}
void PokemonBase::PlayRotateAnim() 
{ 
    //SetAnimState(&rotateAnim); 
    SetAnimState(rotateAnim); 
}

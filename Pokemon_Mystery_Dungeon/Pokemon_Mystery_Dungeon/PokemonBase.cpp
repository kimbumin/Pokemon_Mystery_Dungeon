#include "PokemonBase.h"
#include "PokemonDataLoader.h"

HRESULT PokemonBase::Init()
{
    baseStatus = PokemonDataLoader::GetInstance()->GetData(1);
    currentStatus = *baseStatus;
    level = 5; // 시작 레벨
    CalStatus();
    currentHp = currentStatus.hp;
    return S_OK;
}

void PokemonBase::Release()
{
}

void PokemonBase::Update()
{
}

void PokemonBase::Render(HDC hdc)
{
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
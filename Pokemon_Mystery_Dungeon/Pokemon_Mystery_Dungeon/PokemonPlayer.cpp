#include "PokemonPlayer.h"
#include <cmath>

HRESULT PokemonPlayer::Init()
{
	expToLevelUp = pow((level + 1), 3);
	return PokemonBase::Init();
}

void PokemonPlayer::Release()
{
}

void PokemonPlayer::Update()
{
	PokemonBase::Update();
	if (exp > expToLevelUp)
	{
		LevelUp();
	}
}

bool PokemonPlayer::CanPickUpItem() const
{
	return false;
}

void PokemonPlayer::PickUpItem(Item* item)
{

}

void PokemonPlayer::AddItemToBag(Item* item)
{

}

void PokemonPlayer::UseItem(Item* item)
{

}

void PokemonPlayer::GainExp(int amount)
{
	exp += amount;
}

void PokemonPlayer::LevelUp()
{
	// 진화 체크
	++level;
	expToLevelUp = pow((level + 1), 3);
	CalStatus();
}

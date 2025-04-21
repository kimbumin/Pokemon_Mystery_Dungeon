#include "PokemonPool.h"
#include "PokemonBase.h"

HRESULT PokemonPool::Init()
{
	pokemonPool.resize(20);
	// iterPokemonPool[0] = PlayerManager::GetInstance()->GetPlayer();
	for (iterPokemonPool = begin() + 1; iterPokemonPool != end(); ++iterPokemonPool)
	{
		(*iterPokemonPool) = new PokemonBase;
		(*iterPokemonPool)->SetIsAlive(false);
	}
	return S_OK;
}

void PokemonPool::Release()
{
	for (iterPokemonPool = begin() + 1; iterPokemonPool != end(); ++iterPokemonPool)
	{
		delete (*iterPokemonPool);
		(*iterPokemonPool) = nullptr;
	}
}

void PokemonPool::Update()
{
	for (iterPokemonPool = begin() + 1; iterPokemonPool != end(); ++iterPokemonPool)
	{
		if ((*iterPokemonPool)->GetIsAlive())
		{
			(*iterPokemonPool)->Update();
		}
	}
}

void PokemonPool::Render(HDC hdc)
{
	for (iterPokemonPool = begin() + 1; iterPokemonPool != end(); ++iterPokemonPool)
	{
		if ((*iterPokemonPool)->GetIsAlive())
		{
			(*iterPokemonPool)->Render(hdc);
		}
	}
}

PokemonBase* PokemonPool::Get()
{
	for (int i = 1; i < pokemonPool.size(); ++i)
	{
		if (!pokemonPool[i]->GetIsAlive())
		{
			return pokemonPool[i];
		}
	}
	return nullptr;
}

void PokemonPool::Return(PokemonBase* pokemon)
{
	if (pokemon)
	{
		pokemon->SetIsAlive(false);
	}
}

void PokemonPool::ReturnEnemies()
{
	for (int i = 1; i < pokemonPool.size(); ++i)
	{
		if (pokemonPool[i]->GetIsAlive())
		{
			pokemonPool[i]->SetIsAlive(false);
		}
	}
}

bool PokemonPool::IsEmpty()
{
	for (const auto& pokemon : pokemonPool)
	{
		if (pokemon && pokemon->GetIsAlive())
		{
			return false;
		}
	}
	return true;
}

// 동료가 생기는 상황에서는 구조 개편이 많이 필요할것 같다
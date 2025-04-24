#include "PlayerManager.h"

#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "PokemonPlayer.h"

void PlayerManager::Init()
{
    player = new PokemonPlayer();
    // check 하드 코딩 했음...
    // Bad hard coding
    PokemonImageLoader::GetInstance()->LoadPokemonAnim(4);
    PokemonImageLoader::GetInstance()->LoadPokemonAnim(5);
    PokemonImageLoader::GetInstance()->LoadPokemonAnim(6);
    player->SetIsAlive(true);
    player->SetStatus((PokemonDataLoader::GetInstance()->GetData(4)));
    player->SetLevel(6);

    player->Init();

    player->SetAnimator();
}

void PlayerManager::Release()
{
    if (player)
    {
        player->Release();
        delete player;
        player = nullptr;
    }
    PlayerManager::GetInstance()->ReleaseInstance();
}

void PlayerManager::Update()
{
    player->Update();
}

void PlayerManager::Render(HDC hdc)
{
    player->Render(hdc);
}

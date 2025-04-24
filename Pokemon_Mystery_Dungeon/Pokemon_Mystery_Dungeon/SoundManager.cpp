#include "SoundManager.h"

#include <iostream>

SoundManager* SoundManager::GetInstance()
{
    static SoundManager instance;
    return &instance;
}

void SoundManager::Init()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL Audio Init Error: " << SDL_GetError() << "\n";
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer Init Error: " << Mix_GetError() << "\n";
    }
}

void SoundManager::Release()
{
    for (auto& pair : bgms)
    {
        Mix_FreeMusic(pair.second);
    }
    for (auto& pair : sfxs)
    {
        Mix_FreeChunk(pair.second);
    }
    bgms.clear();
    sfxs.clear();

    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void SoundManager::LoadBGM(const std::string& id, const std::string& path)
{
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (music)
    {
        bgms[id] = music;
    }
    else
    {
        std::cerr << "Failed to load BGM: " << Mix_GetError() << "\n";
    }
}

void SoundManager::LoadSFX(const std::string& id, const std::string& path)
{
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (chunk)
    {
        sfxs[id] = chunk;
    }
    else
    {
        std::cerr << "Failed to load SFX: " << Mix_GetError() << "\n";
    }
}

void SoundManager::PlayBGM(const std::string& id, int loops)
{
    auto it = bgms.find(id);
    if (it != bgms.end())
    {
        Mix_PlayMusic(it->second, loops);
    }
}

void SoundManager::StopBGM()
{
    Mix_HaltMusic();
}

void SoundManager::PlaySFX(const std::string& id, int loops)
{
    auto it = sfxs.find(id);
    if (it != sfxs.end())
    {
        Mix_PlayChannel(-1, it->second, loops);
    }
}

void SoundManager::SetBGMVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

void SoundManager::SetSFXVolume(int volume)
{
    Mix_Volume(-1, volume);  // 모든 채널
}

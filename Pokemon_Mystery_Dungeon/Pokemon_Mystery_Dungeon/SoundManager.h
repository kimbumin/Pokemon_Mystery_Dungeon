#pragma once
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "config.h"

class SoundManager
{
public:
    static SoundManager* GetInstance();
    void Init();
    void Release();

    void LoadBGM(const string& id, const string& path);
    void LoadSFX(const string& id, const string& path);

    void PlayBGM(const string& id, int loops = -1);  // -1: 무한 반복
    void StopBGM();

    void PlaySFX(const string& id, int loops = 0);  // 0: 한 번만 재생
    void SetBGMVolume(int volume);                  // 0~128
    void SetSFXVolume(int volume);                  // 0~128

private:
    SoundManager() = default;
    ~SoundManager() = default;

    map<string, Mix_Music*> bgms;
    map<string, Mix_Chunk*> sfxs;
};

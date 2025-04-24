#pragma once
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#include <map>
#include <string>

class SoundManager
{
public:
    static SoundManager* GetInstance();
    void Init();
    void Release();

    void LoadBGM(const std::string& id, const std::string& path);
    void LoadSFX(const std::string& id, const std::string& path);

    void PlayBGM(const std::string& id, int loops = -1);  // -1: 무한 반복
    void StopBGM();

    void PlaySFX(const std::string& id, int loops = 0);  // 0: 한 번만 재생
    void SetBGMVolume(int volume);                       // 0~128
    void SetSFXVolume(int volume);                       // 0~128

private:
    SoundManager() = default;
    ~SoundManager() = default;

    std::map<std::string, Mix_Music*> bgms;
    std::map<std::string, Mix_Chunk*> sfxs;
};

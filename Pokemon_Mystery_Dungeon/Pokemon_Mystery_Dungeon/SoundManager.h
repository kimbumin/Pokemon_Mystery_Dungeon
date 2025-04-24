#pragma once
#include <SDL2_mixer/SDL_mixer.h>

#include <map>
#include <string>

class SoundManager
{
public:
    bool Init();
    void Release();

    void LoadMusic(const std::string& name, const std::string& path);
    void LoadSFX(const std::string& name, const std::string& path);

    void PlayMusic(const std::string& name, int loops = -1);
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();

    void PlaySFX(const std::string& name, int loops = 0);

private:
    std::map<std::string, Mix_Music*> musicMap;
    std::map<std::string, Mix_Chunk*> sfxMap;
};

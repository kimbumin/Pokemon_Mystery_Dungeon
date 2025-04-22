#pragma once
#include "config.h"

class Image;
using namespace std;

class PokemonAnimator 
{

private:

    struct AnimData 
    {
        Image* image;
        int frameCountX;
        int frameCountY;
        float frameDuration;
        bool looping = true;
        float timer = 0.f;
        bool isFinished = false;
        int currentFrame = 0;
    };


    unordered_map<string, AnimData> animations;
    string currentAnim = "Idle";
    Direction direction = Direction::SOUTH;

public:
    
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc, int x, int y);

    void AddAnimation(const string& name, Image* image, int frameCountX, int frameCountY, float frameDuration, bool loop);
    void Play(const string& name, Direction direction);
    bool IsFinished(const string& name);
    void Clear();
};
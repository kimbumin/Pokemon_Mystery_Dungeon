#include "PokemonAnimator.h"
#include "Image.h"

void PokemonAnimator::Init()
{
}

void PokemonAnimator::Release()
{
}

void PokemonAnimator::Update() 
{
    if (currentAnim.empty()) return;
    auto& data = animations[currentAnim];

    data.timer += TimerManager::GetInstance()->GetDeltaTime();
    if (data.timer >= data.frameDuration) 
    {
        data.timer -= data.frameDuration;
        data.currentFrame++;
        if (data.currentFrame >= data.frameCountX) 
        {
            if (data.looping) 
            {
                data.currentFrame = 0;
            }
            else 
            {
                data.currentFrame = data.frameCountX - 1;
                data.finished = true;
            }
        }
    }
}

void PokemonAnimator::Render(HDC hdc, int x, int y) 
{
    if (currentAnim.empty()) 
    {
        return;
    }
    auto& data = animations[currentAnim];
    if (data.image) 
    {
        data.image->FrameRender(hdc, x, y, data.currentFrame, static_cast<int>(direction));
    }
}

void PokemonAnimator::AddAnimation(const string& name, Image* image,
    int frameCountX, int frameCountY, float frameDuration, bool loop)
{
    animations[name] = { image, frameCountX, frameCountY, frameDuration, loop };
}

void PokemonAnimator::Play(const string& name, Direction dir)
{
    if (animations.find(name) == animations.end()) return;
    if (currentAnim != name)
    {
        currentAnim = name;
        auto& data = animations[name];
        data.currentFrame = 0;
        data.timer = 0.f;
        data.finished = false;
    }
    direction = dir;
}

bool PokemonAnimator::IsFinished(const string& name){
    auto it = animations.find(name);
    if (it != animations.end()) 
    {
        return it->second.finished;
    }
    return false;
}

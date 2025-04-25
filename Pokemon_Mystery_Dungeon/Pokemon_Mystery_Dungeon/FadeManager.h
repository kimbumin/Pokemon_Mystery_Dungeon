#pragma once
#include "config.h"
#include "Singleton.h"

class FadeManager : public Singleton<FadeManager>
{
public:
    FadeManager();

    void StartFadeOut(float speed = 5.0f);
    void StartFadeIn(float speed = 5.0f);

    void Update();
    void Render(HDC hdc, int width, int height);

    bool IsFading() const;
    bool IsFadeComplete() const;

private:
    float alpha;         
    bool isFading;       
    bool fadeOut;        
    float fadeSpeed;     
    COLORREF fadeColor;  

};

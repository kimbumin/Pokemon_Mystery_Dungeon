#pragma once
#include <Windows.h>

#include "Singleton.h"

class Camera : public Singleton<Camera>
{
private:
    POINT cameraPos;   
    POINT mapSize;     
    POINT screenSize;  

    POINT shakeOffset = {0, 0};
    float shakeDuration = 0.0f;  
    int shakeMagnitude = 0;      


public:
    void SetCameraPos(POINT focus);
    POINT GetCameraPos() const;

    void SetMapSize(POINT size)
    {
        mapSize = size;
    }
    void SetScreenSize(POINT size)
    {
        screenSize = size;
    }
    void Update(float deltaTime);              
    void Shake(float duration, int magnitude); 
};

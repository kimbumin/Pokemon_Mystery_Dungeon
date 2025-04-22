#pragma once
#include <Windows.h>

#include "Singleton.h"

class Camera : public Singleton<Camera>
{
private:
    POINT cameraPos;   
    POINT mapSize;     
    POINT screenSize;  

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
};

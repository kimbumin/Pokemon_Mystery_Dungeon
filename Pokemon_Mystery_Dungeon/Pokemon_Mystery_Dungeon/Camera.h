#pragma once
#include <Windows.h>

#include "Singleton.h"

class Camera : public Singleton<Camera>
{
private:
    POINT cameraPos;   // 현재 카메라 위치
    POINT mapSize;     // 전체 맵 크기
    POINT screenSize;  // 현재 화면 크기 (윈도우 크기)

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

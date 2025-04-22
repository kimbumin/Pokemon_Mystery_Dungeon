#include "Camera.h"

void Camera::SetCameraPos(POINT focus)
{
    cameraPos.x = focus.x - screenSize.x / 2;
    cameraPos.y = focus.y - screenSize.y / 2;

    if (cameraPos.x < 0)
        cameraPos.x = 0;
    if (cameraPos.y < 0)
        cameraPos.y = 0;
    if (cameraPos.x + screenSize.x > mapSize.x)
        cameraPos.x = mapSize.x - screenSize.x;
    if (cameraPos.y + screenSize.y > mapSize.y)
        cameraPos.y = mapSize.y - screenSize.y;
}

POINT Camera::GetCameraPos() const
{
    return {cameraPos.x + shakeOffset.x, cameraPos.y + shakeOffset.y};
}

void Camera::Update(float deltaTime)
{
    if (shakeDuration > 0.0f)
    {
        shakeDuration -= deltaTime;

        int offsetX = (rand() % (shakeMagnitude * 2 + 1)) - shakeMagnitude;
        int offsetY = (rand() % (shakeMagnitude * 2 + 1)) - shakeMagnitude;

        shakeOffset = {offsetX, offsetY};
    }
    else
    {
        shakeOffset = {0, 0};
    }
}

void Camera::Shake(float duration, int magnitude)
{
    shakeDuration = duration;
    shakeMagnitude = magnitude;
}

#include "Camera.h"

void Camera::SetCameraPos(POINT focus)
{
    int halfScreenX = static_cast<int>((screenSize.x / zoom) / 2);
    int halfScreenY = static_cast<int>((screenSize.y / zoom) / 2);
    
    cameraPos.x = focus.x - halfScreenX;
    cameraPos.y = focus.y - halfScreenY;


    int maxX = static_cast<int>(mapSize.x - screenSize.x / zoom);
    int maxY = static_cast<int>(mapSize.y - screenSize.y / zoom);

    cameraPos.x = max(0, min(cameraPos.x, maxX));
    cameraPos.y = max(0, min(cameraPos.y, maxY));
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

void Camera::ZoomIn()
{
    zoom += 0.1f;
    if (zoom > maxZoom)
    {
        zoom = maxZoom;
    }
}

void Camera::ZoomOut()
{
    zoom -= 0.1f;
    if (zoom < minZoom)
    {
        zoom = minZoom;
    }
}

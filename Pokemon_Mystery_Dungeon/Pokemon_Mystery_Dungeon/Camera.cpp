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
    return cameraPos;
}

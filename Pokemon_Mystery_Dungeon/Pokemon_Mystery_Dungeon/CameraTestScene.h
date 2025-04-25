#pragma once
#include "GameObject.h"
#include "ImageGDIPlus.h"

class Image;
class CameraTestScene : public GameObject
{
private:
    Image* backGround;

    bool isDialogueBoxOpen = false;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
};

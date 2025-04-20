#pragma once
#include "GameObject.h"

class LoadingScene : public GameObject
{
public:
    LoadingScene();
    virtual ~LoadingScene();

    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;

private:
    int frameCount;

};
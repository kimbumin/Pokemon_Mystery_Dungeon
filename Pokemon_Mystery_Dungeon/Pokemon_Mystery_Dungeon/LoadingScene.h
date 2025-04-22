#pragma once
#include "Scene.h"

class LoadingScene : public Scene
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
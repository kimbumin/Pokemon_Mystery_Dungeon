#pragma once
#include "Singleton.h"
// clang-format off
#include "config.h"
// clang-format on
class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
    map<string, Scene*> mapScenes;
    map<string, Scene*> mapLoadingScenes;

public:
    static Scene* currentScene;
    static Scene* loadingScene;
    static Scene* nextScene;

    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    HRESULT ChangeScene(string key);
    HRESULT ChangeScene(string key, string loadingKey);

    Scene* AddScene(string key, Scene* scene);
    Scene* AddLoadingScene(string key, Scene* scene);
};

#pragma once
#include "Singleton.h"
#include "UIState.h"

class UIManager : public Singleton<UIManager>
{
    friend class Singleton<UIManager>;

private:
    map<string, UIState*> UiStateMap;  // UI 상태를 저장하는 맵
    map<string, bool> IsOpenMap;
    string currentStateKey;

    static UIState* currentState;
    static UIState* nextState;

    vector<UIState*> persistentStates;
    vector<UIState*> toggleStates;

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);
    HRESULT ChangeState(string key);
    UIState* AddState(string key, UIState* state);
    UIState* FindState(const string& key);
    void RegisterAllUIStates();

    void OpenUIStateBox(const string& key);
    void CloseUIStateBox(const string& key);

    void AddPersistentState(UIState* state);
    void AddToggleState(UIState* state, bool isOpen);
};

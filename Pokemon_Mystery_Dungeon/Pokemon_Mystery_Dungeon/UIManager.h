#pragma once
#include "Singleton.h"
#include "UIState.h"

class UIState;
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

    DungeonType dungeonType = DungeonType::DUNGEON_TYPE_ICE;

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
    const string& GetCurrentStateKey() const
    {
        return currentStateKey;
    }

    void AddPersistentState(UIState* state);
    void AddToggleState(UIState* state, bool isOpen);
    

    DungeonType GetDungeonType()
    {
        return dungeonType;
    }
    void SetDungeonType(DungeonType type)
    {
        dungeonType = type;
    }


};

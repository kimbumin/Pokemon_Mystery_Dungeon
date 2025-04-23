#include "UIManager.h"

#include "DefaultUIState.h"
#include "DialogueUIState.h"
#include "DungeonUIState.h"
#include "InfoUIState.h"
#include "SkillInfoUIState.h"
#include "SkillUIState.h"
#include "UIState.h"
#include "YesOrNoUIState.h"
#include "IdleUIState.h"
#include "DownStairUIState.h"


UIState* UIManager::currentState = nullptr;
UIState* UIManager::nextState = nullptr;

void UIManager::Init()
{
    AddPersistentState(new InfoUIState());

    RegisterAllUIStates();
}

void UIManager::Release()
{
    for (auto& pair : UiStateMap)
    {
        if (pair.second)
        {
            pair.second->Release();
            delete pair.second;
        }
    }
    UiStateMap.clear();

    for (auto* state : persistentStates)
    {
        delete state;
    }
    persistentStates.clear();

    toggleStates.clear();

    currentState = nullptr;
    currentStateKey.clear();
    ReleaseInstance();
}

void UIManager::Update()
{
    for (auto& state : persistentStates)
    {
        state->Update();
    }

    for (auto& state : toggleStates)
    {
        state->Update();
    }

    if (currentState)
    {
        currentState->Update();
    }
}

void UIManager::Render(HDC hdc)
{
    for (auto& state : persistentStates)
    {
        state->Render(hdc);
    }

    for (auto& state : toggleStates)
    {
        state->Render(hdc);
    }

    if (currentState)
    {
        currentState->Render(hdc);
    }
}

HRESULT UIManager::ChangeState(string key)
{
    auto it = UiStateMap.find(key);
    if (it == UiStateMap.end())
        return E_FAIL;

    if (it->second == currentState)
        return S_OK;

    if (currentState)
    {
        currentState->Release();
    }
    currentState = it->second;
    currentStateKey = key;

    if (currentState)
    {
        currentState->Init();
        return S_OK;
    }
    return E_FAIL;
}

UIState* UIManager::AddState(string key, UIState* state)
{
    if (state == nullptr)
    {
        return nullptr;
    }

    auto iter = UiStateMap.find(key);
    if (iter != UiStateMap.end())
    {
        return iter->second;
    }

    UiStateMap.insert(make_pair(key, state));

    return state;
}

UIState* UIManager::FindState(const string& key)
{
    auto iter = UiStateMap.find(key);
    if (iter != UiStateMap.end())
    {
        return iter->second;
    }
    return nullptr;
}

void UIManager::RegisterAllUIStates()
{
    AddState("IdleUI", new IdleUIState());
    AddState("dialogueBox", new DialogueUIState());
    AddState("defaultUI", new DefaultUIState());
    AddState("SkillUI", new SkillUIState());
    AddState("SkillUseUI", new SkillInfoUIState());
    AddState("DungeonUI", new DungeonUIState());
    AddState("YesOrNoUI", new YesOrNoUIState());
    AddState("DownStairUI", new DownStairUIState());
}

void UIManager::OpenUIStateBox(const string& key)
{
    bool& isActive = IsOpenMap[key];
    isActive = !isActive;

    if (isActive)
    {
        ChangeState(key);
    }
    else
    {
        currentState = nullptr;
    }
}

void UIManager::CloseUIStateBox(const string& key)
{
    if (currentStateKey == key)
    {
        currentState = nullptr;
        currentStateKey = "";
    }
}

void UIManager::AddPersistentState(UIState* state)
{
    if (state)
    {
        state->Init();
        persistentStates.push_back(state);
    }
}

void UIManager::AddToggleState(UIState* state, bool isOpen)
{
    auto iter = find(toggleStates.begin(), toggleStates.end(), state);
    if (isOpen)
    {
        if (iter == toggleStates.end())
        {
            toggleStates.push_back(state);
        }
    }
    else
    {
        if (iter != toggleStates.end())
        {
            toggleStates.erase(iter);
        }
    }
}

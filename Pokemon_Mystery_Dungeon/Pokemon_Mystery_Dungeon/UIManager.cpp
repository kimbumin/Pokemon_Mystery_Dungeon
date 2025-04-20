#include "UIManager.h"
#include "UIState.h"
#include "DialogueUIState.h"
#include "DefaultUIState.h"
#include "SkillUIState.h"
#include "SkillInfoUIState.h"
#include "DungeonUIState.h"

UIState* UIManager::currentState = nullptr;
UIState* UIManager::nextState = nullptr;

void UIManager::Init()
{
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
	currentState = nullptr;
	currentStateKey.clear();
	ReleaseInstance();
}

void UIManager::Update()
{
	if (currentState)
	{
		currentState->Update();
	}
}

void UIManager::Render(HDC hdc)
{
	if (currentState)
	{
		currentState->Render(hdc);
	}
}

HRESULT UIManager::ChangeState(string key)
{
	auto it = UiStateMap.find(key);
	if (it == UiStateMap.end()) return E_FAIL;

	if (it->second == currentState) return S_OK;

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
	AddState("dialogueBox", new DialogueUIState());
	AddState("defaultUI", new DefaultUIState());
	AddState("SkillUI", new SkillUIState());
	AddState("SkillUseUI", new SkillInfoUIState());
	AddState("DungeonUI", new DungeonUIState());
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



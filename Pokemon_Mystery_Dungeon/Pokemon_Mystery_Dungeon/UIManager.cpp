#include "UIManager.h"
#include "UIState.h"
#include "DialogueUIState.h"
#include "DefaultUIState.h"

UIState* UIManager::currentState = nullptr;
UIState* UIManager::nextState = nullptr;

void UIManager::Init()
{
}

void UIManager::Release()
{
	map<string, UIState*>::iterator iter;
	for (iter = UiStateMap.begin(); iter != UiStateMap.end(); iter++)
	{
		if (iter->second)
		{
			iter->second->Release();
			delete iter->second;
			iter->second = nullptr;
		}
	}
	UiStateMap.clear();
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
	auto iter = UiStateMap.find(key);
	if (iter == UiStateMap.end())
	{
		return E_FAIL;
	}

	if (iter->second == currentState)
	{
		return S_OK;
	}

	if (SUCCEEDED(iter->second->Init()))
	{
		if (currentState)
		{
			currentState->Release();
		}
		currentState = iter->second;
		nextState = nullptr;
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

void UIManager::RegisterAllUIStates()
{
	AddState("dialogueBox", new DialogueUIState());
	AddState("defaultBox", new DefaultUIState());
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



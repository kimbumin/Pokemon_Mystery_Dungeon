#include "UIManager.h"
#include "UIState.h"

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

void UIManager::AddState(string key, UIState* state)
{
}

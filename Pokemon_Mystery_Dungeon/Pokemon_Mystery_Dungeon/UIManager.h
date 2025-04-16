#pragma once
#include "UIState.h"
#include "Singleton.h"

class UIManager : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

private:
	map<string, UIState*> UiStateMap; // UI 상태를 저장하는 맵


public:
	static UIState* currentState;
	static UIState* nextState;

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	HRESULT ChangeState(string key);
	UIState* AddState(string key, UIState* state);

};


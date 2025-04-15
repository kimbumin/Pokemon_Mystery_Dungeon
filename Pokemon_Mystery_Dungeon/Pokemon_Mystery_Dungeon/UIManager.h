#pragma once
#include "UIState.h"
#include "Singleton.h"

class UIManager : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

private:
	UIState* currentState = nullptr;
	UIState* nextState = nullptr;

	UIManager() = default;
	~UIManager();

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void ChangeState(UIState* state);

};


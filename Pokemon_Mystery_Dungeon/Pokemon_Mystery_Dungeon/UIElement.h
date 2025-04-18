#pragma once
#include "Config.h"
#include <vector>
#include <Windows.h>

class UIElement
{
protected:
	UIElement* parent = nullptr;
	vector<UIElement*> children;

	FPOINT localPos{ 0,0 };
	FPOINT realPos{ 0,0 };

public:
	UIElement() = default;
	virtual ~UIElement() = default;

	void SetParent(UIElement* newParent);

	void UpdateRealPos();

	virtual void Update();
	virtual void Render(HDC hdc);

	void SetLocalPos(float x, float y) { localPos = { x, y }; }
	FPOINT GetLocalPos() const { return localPos; }
	FPOINT GetRealPos() const { return realPos; }
};


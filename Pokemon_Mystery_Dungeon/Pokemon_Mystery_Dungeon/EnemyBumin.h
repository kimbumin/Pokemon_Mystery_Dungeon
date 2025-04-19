#pragma once
#include "GameObject.h"
class EnemyBumin :GameObject
{
private:
	FPOINT pos;
	int HP;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	inline int GetX() { return pos.x; }
	inline int GetY() { return pos.y; }
	inline int GetHP() { return HP; }
	inline void SetHP(int newHP) { HP = newHP; }
};


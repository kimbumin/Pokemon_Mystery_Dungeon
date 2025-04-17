#pragma once
#include "IItem.h"
#include "Image.h"
#include "ISkill.h"

class Image;
class ISkill;
class PPHeal : public IItem {
private:
	Image* image;
	ISkill* skillPP;

	int x;
	int y;
	int healPP;
	string name;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void Use() override;
	virtual void SetPosition(int newX, int newY) override;

	inline virtual int GetX() const override { return x; }
	inline virtual int GetY() const override { return y; }
};

// IItem.h
#pragma once
#include "GameObject.h"

class IItem : public GameObject {
public:
	virtual ~IItem() {}
	virtual void Use() = 0;
	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
	virtual void SetPosition(int x, int y) = 0;
};


#pragma once
#include "GameObject.h"

struct SkillData {
	int number;
	string name;
	string element;
	string type;
	string animAction;
	int power;
	int accuracy;
	int pp;
};

class PokemonBase;

class ISkill : public GameObject {
protected:
	SkillData data;
	FPOINT pos;
	int direction;
	bool isActive;

public:
	ISkill() = default;

	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Use(PokemonBase* owner) = 0;
	virtual shared_ptr<ISkill> Clone() = 0;

	// getter ÇÔ¼öµé
	inline string GetName() const { return data.name; }
	inline string GetElement() const { return data.element; }
	inline string GetSkillType() const { return data.type; }
	inline string GetAnimAction() const { return data.animAction; }
	inline int GetPower() const { return data.power; }
	inline int GetAccuracy() const { return data.accuracy; }
	inline const SkillData& GetSkillData() const { return data; }

	virtual ~ISkill() = default;
};

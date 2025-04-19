#pragma once
#include "ISkill.h"
#include "config.h"
#include "Image.h"
#include "PlayerBumin.h"
#include "EnemyBumin.h"

class Image;
class StoneShowerSkill : public ISkill {
private:
	Image* image;

	enum class ElementType { ROCK };
	enum class SkillType { PHYSICS };

	FPOINT pos;
	string name;
	struct SkillStats {
		int power;
		int accuracy;
		int maxPP;
	} stats;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Use(PlayerBumin* user, EnemyBumin* target) override;
	shared_ptr<ISkill> Clone() const override;

	string GetName() const override { return name; }
	string GetElement() const override { return "ROCK"; }
	string GetType() const override { return "PHYSICS"; }
	int GetPower() const override { return stats.power; }
	int GetAccuracy() const override { return stats.accuracy; }
};

#pragma once
#include "ISkill.h"
#include "config.h"
#include "Image.h"

class Image;
class PokemonBase;
class EmberSkill : public ISkill {
private:
	Image* image;
	float elapsedTime;
	int frameCount;

public:
	EmberSkill() = default;
	EmberSkill(const SkillData& skillData);

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Use(PokemonBase* owner) override;
	shared_ptr<ISkill> Clone() override;
};

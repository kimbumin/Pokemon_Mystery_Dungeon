#pragma once
#include "ISkill.h"
#include "config.h"
#include "Image.h"

class Image;
class PokemonBase;
class EmberSkill : public ISkill {
private:
	Image* image;
	FPOINT pos;
	string name;
	SkillData data;
	int direction;
	bool isActive;

	float elapsedTime;
	bool isActive;  // 스킬 효과가 활성화되어 있는지 여부
	int frameCount;  // 애니메이션 프레임 카운트 (필요한 경우)

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Use(PokemonBase* owner) const override;
	shared_ptr<ISkill> Clone() const override;
};

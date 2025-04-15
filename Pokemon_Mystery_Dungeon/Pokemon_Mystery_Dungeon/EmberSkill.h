#pragma once
#include "ISkill.h"
#include "config.h"

class Image;
class EmberSkill : public ISkill {
private:
    Image* image = nullptr;

    enum class ElementType { Fire };
    enum class SkillType { Special };
    string name = "Ember";

    struct SkillStats {
        int power = 40;
        int accuracy = 100;
        int maxPP = 25;
    } stats;

public:
    void Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Use() override;

    string GetName() const override { return name; }
    string GetElement() const override { return "Fire"; }
    string GetType() const override { return "Special"; }
    int GetPower() const override { return stats.power; }
    int GetAccuracy() const override { return stats.accuracy; }
};

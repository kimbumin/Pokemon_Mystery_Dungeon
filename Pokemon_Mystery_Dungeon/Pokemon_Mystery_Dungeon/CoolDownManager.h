#pragma once
#include "config.h"
#include <string>
#include "Singleton.h"

class CoolDownManager : public Singleton<CoolDownManager>
{
    friend class Singleton<CoolDownManager>;

private:

    unordered_map<string, float> coolDowns;

    CoolDownManager() = default;
    ~CoolDownManager() = default;

    public:
    void SetCoolDown(const string& key, float coolDownTime);
    bool IsCooldown(const string& key) const;
    float GetRemainingTime(const string& key) const;
    void Update(float dt);
};

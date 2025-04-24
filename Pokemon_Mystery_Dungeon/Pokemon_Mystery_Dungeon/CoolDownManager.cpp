#include "CoolDownManager.h"

void CoolDownManager::SetCoolDown(const string& key, float coolDownTime)
{
    coolDowns[key] = coolDownTime;
}

bool CoolDownManager::IsCooldown(const string& key) const
{
    auto it = coolDowns.find(key);

    return it != coolDowns.end() && it->second > 0.0f;
}

float CoolDownManager::GetRemainingTime(const string& key) const
{
    auto it = coolDowns.find(key);
    if (it != coolDowns.end())
    {
        return it->second;
    }
    return 0.0f;
}

void CoolDownManager::Update(float dt)
{
    for (auto& pair : coolDowns)
    {
        pair.second -= dt;
        if (pair.second < 0.0f)
        {
            pair.second = 0.0f;
        }
    }
}

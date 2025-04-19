#pragma once
#include "ISkill.h"
#include "GameObject.h"

class SkillManager : public GameObject {
private:
    unordered_map<string, shared_ptr<ISkill>> skillMap;

public:
    void RegisterSkill(const string& name, shared_ptr<ISkill> skill);
    void UseSkill(const string& skillName, PlayerBumin* user, EnemyBumin* target);
    void Release();

    shared_ptr<ISkill> CreateSkill(const string& name);
    shared_ptr<ISkill> FindSkill(const string& name);
};

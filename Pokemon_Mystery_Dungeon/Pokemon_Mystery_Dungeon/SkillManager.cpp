#pragma once
#include "SkillManager.h"

// 스킬 등록 (이름과 스킬 객체를 등록)
void SkillManager::RegisterSkill(const string& name, shared_ptr<ISkill> skill)
{
	skillMap[name] = skill;
}

// 스킬 사용 (사용자와 대상에게 스킬 사용)
void SkillManager::UseSkill(const string& skillName, GameObject* user, GameObject* target)
{
	auto it = skillMap.find(skillName);
	if (it != skillMap.end())
	{
		it->second->Use(user, target);
	}
}

void SkillManager::Release()
{
	skillMap.clear();
}

// 스킬 생성 (여기선 이미 등록된 스킬을 반환)
shared_ptr<ISkill> SkillManager::CreateSkill(const string& name)
{
	auto it = skillMap.find(name);
	if (it != skillMap.end())
	{
		return it->second->Clone();  // 스킬 복제본을 반환
	}
	return nullptr;
}

// 스킬 찾기 (이름으로 스킬 반환)
shared_ptr<ISkill> SkillManager::FindSkill(const string& name)
{
	auto it = skillMap.find(name);
	if (it != skillMap.end())
	{
		return it->second;  // 스킬 객체 반환
	}
	return nullptr;
}


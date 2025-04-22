#pragma once
#include "ISkill.h"
#include "GameObject.h"

class SkillManager {
private:

	string line;
	SkillData data;
	string token;
	map<string, shared_ptr<ISkill>> skillMap;

public:
	void LoadSkillsFromCSV(const string& filepath);
	shared_ptr<ISkill> CreateSkill(const string& name);
	shared_ptr<ISkill> FindSkill(const string& name);
	void Release();
};


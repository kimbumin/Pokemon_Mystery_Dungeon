#include "SkillManager.h"

void SkillManager::LoadSkillsFromCSV(const string& filepath)
{
    ifstream file(filepath);
    if (!file.is_open()) {
        OutputDebugStringA(("Failed to open CSV file: " + filepath + "\n").c_str());
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        getline(iss, token, ','); data.number = stoi(token);
        getline(iss, data.name, ',');
        getline(iss, data.element, ',');
        getline(iss, data.type, ',');
        getline(iss, data.animAction, ','); 
        getline(iss, token, ','); data.power = stoi(token);
        getline(iss, token, ','); data.accuracy = stoi(token);
        getline(iss, token, ','); data.pp = stoi(token);


        auto skill = make_shared<ISkill>(data);
        skillMap[data.name] = skill; // 이름 기반으로 저장
    }

    file.close();
}

shared_ptr<ISkill> SkillManager::CreateSkill(const string& name)
{
    auto it = skillMap.find(name);
    if (it != skillMap.end()) {
        return it->second->Clone(); // 복제해서 새 인스턴스 반환
    }
    return nullptr;
}

shared_ptr<ISkill> SkillManager::FindSkill(const string& name)
{
    auto it = skillMap.find(name);
    if (it != skillMap.end()) {
        return it->second;
    }
    return nullptr;
}

void SkillManager::Release()
{
    skillMap.clear();
}

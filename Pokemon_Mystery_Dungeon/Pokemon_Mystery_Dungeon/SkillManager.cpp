#include "SkillManager.h"

#include "EmberSkill.h"
#include "FireBlastSkill.h"

void SkillManager::LoadSkillsFromCSV(const string& filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        OutputDebugStringA(
            ("Failed to open CSV file: " + filepath + "\n").c_str());
        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;
        if (line.empty())
            continue;

        istringstream iss(line);
        string token;
        SkillData data = {};

        try
        {
            getline(iss, token, ',');
            if (token.empty())
                throw invalid_argument("Empty Number");
            data.number = stoi(token);

            getline(iss, token, ',');
            data.name = token;  // ★ 이름 읽기

            getline(iss, token, ',');
            data.power = token.empty() ? 0 : stoi(token);

            getline(iss, token, ',');
            data.accuracy = token.empty() ? 0 : stoi(token);

            getline(iss, token, ',');
            data.pp = token.empty() ? 0 : stoi(token);

            if (data.name.empty())
                throw invalid_argument("Skill Name is empty");

            // 등록된 스킬이면 복제, 아니면 power 기준으로 생성
            auto it = skillMap.find(data.name);
            if (it != skillMap.end())
            {
                skillMap[data.name] = it->second->Clone();
            }
            else
            {
                if (data.power >= 70)
                {
                    // skillMap[data.name] = make_shared<SwingSkill>(data);
                }
                else
                {
                    // skillMap[data.name] = make_shared<AttackSkill>(data);
                }
            }
            skillMap[data.name]->Init();
        }
        catch (const exception& e)
        {
            string errorMsg = "Error parsing CSV at line " +
                              to_string(lineNumber) + ": " + e.what() + "\n";
            OutputDebugStringA(errorMsg.c_str());
            continue;
        }
    }

    file.close();
}

shared_ptr<ISkill> SkillManager::CreateSkill(const string& name)
{
    auto it = skillMap.find(name);
    if (it != skillMap.end())
    {
        return it->second->Clone();
    }
    return nullptr;
}

shared_ptr<ISkill> SkillManager::FindSkill(const string& name)
{
    auto it = skillMap.find(name);
    if (it != skillMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void SkillManager::Release()
{
    skillMap.clear();
}

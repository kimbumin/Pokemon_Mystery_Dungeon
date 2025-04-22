#include "SkillManager.h"

#include "EmberSkill.h"

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
            continue;  // 빈 줄 무시

        istringstream iss(line);
        string token;
        SkillData data = {};

        try
        {
            // 순서대로 읽기
            getline(iss, token, ',');
            if (token.empty())
                throw invalid_argument("Empty Number");
            data.number = stoi(token);

            if (!getline(iss, data.name, ','))
                throw invalid_argument("Missing Name");
            if (!getline(iss, data.element, ','))
                throw invalid_argument("Missing Element");
            if (!getline(iss, data.type, ','))
                throw invalid_argument("Missing Type");
            if (!getline(iss, data.animAction, ','))
                data.animAction = "Normal";  // animAction은 기본값

            getline(iss, token, ',');
            data.power = token.empty() ? 0 : stoi(token);

            getline(iss, token, ',');
            data.accuracy = token.empty() ? 0 : stoi(token);

            getline(iss, token, ',');
            data.pp = token.empty() ? 0 : stoi(token);

            if (data.name.empty())
                throw invalid_argument("Skill Name is empty");

            // 스킬 등록
            skillMap[data.name] = make_shared<EmberSkill>(data);
            skillMap[data.name]->Init();
        }
        catch (const exception& e)
        {
            string errorMsg = "Error parsing CSV at line " +
                              to_string(lineNumber) + ": " + e.what() + "\n";
            OutputDebugStringA(errorMsg.c_str());
            continue;  // 문제 있는 줄은 건너뜀
        }
    }

    file.close();
}

shared_ptr<ISkill> SkillManager::CreateSkill(const string& name)
{
    auto it = skillMap.find(name);
    if (it != skillMap.end())
    {
        return it->second->Clone();  // 복제해서 새 인스턴스 반환
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

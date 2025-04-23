#pragma once
#include <string>

namespace DialogueTemplate
{
inline const std::wstring FoundItem = L"You obtained <itemName>.";
inline const std::wstring GainedExp = L"You gained <exp> EXP.";
inline const std::wstring FoundObject = L"You found <target>.";
inline const std::wstring ArrivedAtLocation = L"You arrived at <location>.";
inline const std::wstring StatusEffect =
    L"You are now affected by <effectName>.";
inline const std::wstring EnemyFled = L"<enemyName> has fled.";
}  // namespace DialogueTemplate

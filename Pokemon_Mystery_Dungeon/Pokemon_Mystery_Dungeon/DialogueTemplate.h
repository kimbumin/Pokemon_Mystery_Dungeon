namespace DialogueTemplate
{
// 아이템 및 탐색 관련
inline const std::wstring FoundItem = L"You obtained <itemName>.";
// <itemName>을(를) 손에 넣었다!

inline const std::wstring GainedExp = L"You gained <exp> EXP.";
// <exp>의 경험치를 얻었다!

// 전투 관련
inline const std::wstring UsedSkill = L"<userName> used <skillName>!";
// <userName>은(는) <skillName>을(를) 사용했다!

inline const std::wstring TookDamage =
    L"<targetName> took <damage> damage!";
// <targetName>은(는) <damage>의 데미지를 입었다!

inline const std::wstring Fainted = L"<targetName> fainted!";
// <targetName>은(는) 쓰러졌다!

inline const std::wstring NoPPLeft = L"No PP left for <skillName>!";
// <skillName>의 PP가 없다!

// 공격 효과
inline const std::wstring SuperEffective = L"It's super effective!";
// 효과가 굉장했다!

inline const std::wstring NotVeryEffective = L"It's not very effective...";
// 별로였다...

inline const std::wstring NoEffect = L"It has no effect...";
// 전혀 효과가 없다...

// 레벨업 / 진화
inline const std::wstring LevelUp = L"<pokemonName> grew to Lv.<level>!";
// <pokemonName>의 레벨이 <level>이(가) 되었다!

inline const std::wstring Evolution = L"<oldName> evolved into <newName>!";
// <oldName>은(는) <newName>으로 진화했다!

inline const std::wstring LevelUpSummary = L"Level up! <statChanges>!";
// 레벨업! <statChanges>!

// 아이템 사용
inline const std::wstring UsedItem = L"<userName> used <itemName>.";
// <userName>은(는) <itemName>을(를) 사용했다!

inline const std::wstring RestoredHP =
    L"<pokemonName> restored <amount> HP!";
// <pokemonName>의 HP가 <amount> 회복되었다!

inline const std::wstring RestoredPP =
    L"<skillName>'s PP was restored by <amount>!";
// <skillName>의 PP가 <amount> 회복되었다!

// 던전 탐색 / 진행
inline const std::wstring DungeonCleared = L"You cleared the dungeon!";
// 던전을 클리어했다!

inline const std::wstring ProceedToNextFloor = L"You moved to the next floor.";
// 다음 층으로 내려갔다!

inline const std::wstring RescueFailed = L"The rescue failed...";
// 구조에 실패했다...
}  // namespace DialogueTemplate
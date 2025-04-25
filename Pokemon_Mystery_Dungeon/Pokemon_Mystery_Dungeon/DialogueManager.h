#pragma once
#include <map>
#include <string>

#include "Singleton.h"

class DialogueManager : public Singleton<DialogueManager>
{
public:
    // 텍스트 템플릿 + 치환 값으로 대화 1줄 출력
    void ShowLine(const std::wstring& templateText,
                  const std::map<std::wstring, std::wstring>& values);

};

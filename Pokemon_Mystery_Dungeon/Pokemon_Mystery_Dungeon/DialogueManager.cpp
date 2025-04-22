#define _HAS_STD_BYTE 0
#include <Windows.h>
#undef byte

#include "DialogueManager.h"
<<<<<<< HEAD
#include "UIManager.h"
=======
// clang-format off
#include "UIManager.h"
// clang-format on
>>>>>>> 420477f2d853bea84d9b717ac003b409f7d69c40
#include "DialogueTemplate.h"
#include "DialogueUIState.h"

// text: 템플릿 문자열 (예: "'아이템명'을 획득했습니다")
// values: 템플릿에서 치환할 변수 값들 (예: { {"아이템명", "몬스터볼"} })
void DialogueManager::ShowLine(const wstring& templateText,
                               const map<wstring, wstring>& values)
{
    // 대화창 상태로 전환
    UIManager::GetInstance()->ChangeState("dialogueBox");

    // 현재 상태를 DialogueUIState로 캐스팅해서 찾음
    auto* state = dynamic_cast<DialogueUIState*>(
        UIManager::GetInstance()->FindState("dialogueBox"));
    if (state)
    {
        // 텍스트 + 치환 map 전달
        state->PushDialogueLine(templateText, values);
    }
}

/*
* 내가 헷갈려서 자주 다시 보려고 정리해둔 주석

- dynamic_cast를 사용하는 이유:
    UIManager는 모든 UI 상태를 공통 타입인 UIState*로 관리함
    하지만 대화창에서만 사용하는 PushDialogueLine() 같은 함수는
    UIState*로는 사용할 수 없기 때문에
    실제 타입이 DialogueUIState인지 확인해서 안전하게 형변환해야 함
    → 그게 dynamic_cast

    dynamic_cast는 "이 UI가 진짜 대화상자 맞아?"라고 체크하고 변환해주는 안전한
도구임 안 쓰면 → 타입 안 맞을 때도 실행돼서 크래시 날 수 있음.

- 예시:
    auto* state =
dynamic_cast<DialogueUIState*>(UIManager::GetInstance()->FindState("dialogueBox"));

- 내가 원래 하고 싶었던 구조:
    if (I 키를 누르면)
    {
        대화상자를 만든다;
        대사 한 줄을 추가한다;
        화면에 그린다;
    }

    → 이 구조는 보기엔 간단하지만,
      대화 로그를 띄울 때마다 대화창을 새로 만들고,
      Init(), Update(), Render()도 매번 직접 호출해야 함

    → 지금 구조는 대화창은 UIManager가 한 번만 만들고 관리해주고,
      난 그냥 대사 한 줄만 추가하면 됨
      코드는 길어 보이지만, 훨씬 효율적이고 안전함 하지만 이해가 어려움
*/

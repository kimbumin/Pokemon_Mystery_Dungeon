#pragma once
#include "UIState.h"

class UIElementImage;

class DialogueUIState : public UIState
{
private:
    UIElementImage* dialogueBoxImage = nullptr;

    const int dialogueBoxPosX = 25;
    const int dialogueBoxPosY = 220;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Update(float dt) override;
    void Render(HDC hdc) override;
    ~DialogueUIState() override;

    // 외부에서 텍스트 1줄 추가
    void PushDialogueLine(const wstring& text);

    void PushDialogueLine(const wstring& text,
                          const map<wstring, wstring>& values);
};

#include "DialogueUIState.h"

#include "ImageGDIPlusManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIManager.h"

DialogueUIState::~DialogueUIState()
{
    Release();
}

HRESULT DialogueUIState::Init()
{
    // 대화 상자 이미지 생성
    dialogueBoxImage = new UIElementImage();
    dialogueBoxImage->SetImage(ImageGDIPlusManager::GetInstance()->AddImage(
        "dialogueBox", L"Image/UIImage/DialogueUIState/DialogueBoxImage.png", 1,
        1));

    dialogueBoxImage->SetLocalPos(dialogueBoxPosX, dialogueBoxPosY);
    dialogueBoxImage->setAlpha(0.95f);

    dialogueBoxImage->UpdateRealPos();

    mainText = new UIElementText();
    mainText->SetFont(20);
    mainText->SetTextLine(5.0f);
    mainText->SetTextColorRGB(28, 28, 132);
    mainText->SetLocalPos(20, 30);
    mainText->SetParent(dialogueBoxImage);

    return (dialogueBoxImage != nullptr) ? S_OK : E_FAIL;
}

void DialogueUIState::Release()
{
    delete dialogueBoxImage;  // 자식 자동 정리
    dialogueBoxImage = nullptr;
}

void DialogueUIState::Update()
{
    if (dialogueBoxImage)
        dialogueBoxImage->Update();

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X' 키
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        UIManager::GetInstance()->CloseUIStateBox("dialogueBox");
    }
}

void DialogueUIState::Update(float dt)
{
    if (dialogueBoxImage)
        dialogueBoxImage->Update(dt);

    if (mainText)
        mainText->Update(dt);


    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X'
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        UIManager::GetInstance()->CloseUIStateBox("dialogueBox");
        isActive = false;
        return;
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A))  // 'Z'
    {
        // SoundManager::GetInstance()->PlaySFX("button");
        if (mainText && !mainText->IsTypingFinished())
        {
            // 타이핑 중이면 즉시 전체 출력
            mainText->SkipTyping();
            return;
        }
        else if (dialogueFullyShown)
        {
            // 타이핑 끝난 상태면 다음 대사로 넘어감
            PopNextDialogueLine();
            return;
        }
    }
    

    if (mainText && !dialogueFullyShown && mainText->IsTypingFinished())
    {
        dialogueFullyShown = true;
        closeTimer = 0.0f;  
    }

    if (dialogueFullyShown)
    {
        closeTimer += dt;
        if (closeTimer >= 2.0f)
        {
            PopNextDialogueLine();
        }
    }

    
}

void DialogueUIState::Render(HDC hdc)
{
    if (dialogueBoxImage)
        dialogueBoxImage->Render(hdc);
}

void DialogueUIState::PushDialogueLine(const wstring& text)
{
    auto* newText = new UIElementText();
    newText->SetText(text);
    newText->SetFont(18);
    newText->SetTextLine(5.0f);
    newText->SetLocalPos(10, 10);
    newText->SetParent(dialogueBoxImage);
}

void DialogueUIState::PushDialogueLine(const wstring& text,
                                       const map<wstring, wstring>& values)
{
    if (!mainText)
        return;

    const wstring& replaced = mainText->RenderDialogue(text, values);
    mainText->TypeEffect(replaced, 0.05f);

    dialogueFullyShown = false;
    closeTimer = 0.0f;
}

void DialogueUIState::QueueDialogueLine(const wstring& text,
                                        const map<wstring, wstring>& values)
{
    dialogueQueue.push({text, values});

    if (!isActive)
    {
        PopNextDialogueLine();
    }
}

void DialogueUIState::PopNextDialogueLine()
{
    if (dialogueQueue.empty())
    {
        UIManager::GetInstance()->CloseUIStateBox("dialogueBox");
        isActive = false;

        return;
    }

    const auto& [text, values] = dialogueQueue.front();
    const std::wstring& replaced = mainText->RenderDialogue(text, values);
    mainText->TypeEffect(replaced, 0.05f);

    dialogueFullyShown = false;
    closeTimer = 0.0f;
    isActive = true;

    dialogueQueue.pop();
}

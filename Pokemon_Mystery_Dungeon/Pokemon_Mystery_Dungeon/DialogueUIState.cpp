#include "DialogueUIState.h"
#include "ImageManager.h"

DialogueUIState::~DialogueUIState()
{
}

HRESULT DialogueUIState::Init()
{
	dialogueBoxImage = ImageManager::GetInstance()->AddImage("DialogueBox", TEXT("Image/UIImage/DialogueBox.bmp"), 300, 183, false, RGB(255,255,255));
	return (dialogueBoxImage != nullptr) ? S_OK : E_FAIL;
}

void DialogueUIState::Release()
{
}

void DialogueUIState::Update()
{

}

void DialogueUIState::Render(HDC hdc)
{
	if (dialogueBoxImage)
	{

		dialogueBoxImage->Render(hdc, dialogueBoxX, dialogueBoxY);
	}
}

#include "DialogueUIState.h"
#include "ImageGDIPlusManager.h"

DialogueUIState::~DialogueUIState()
{
}

HRESULT DialogueUIState::Init()
{
	dialogueBoxImage = ImageGDIPlusManager::GetInstance()->AddImage("dialogueBox", L"Image/UIImage/DialogueBoxImage.png", 1, 1);
	//dialogueBoxImage2 = ImageGDIPlusManager::GetInstance()->AddImage("dialogueBox2", L"Image/UIImage/DialogueBoxImage.png", 1, 1);
	//dialogueBoxImage3 = ImageGDIPlusManager::GetInstance()->AddImage("dialogueBox3", L"Image/UIImage/DialogueBoxImage.png", 1, 1);
	return (dialogueBoxImage != nullptr) ? S_OK : E_FAIL;
	return S_OK;
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

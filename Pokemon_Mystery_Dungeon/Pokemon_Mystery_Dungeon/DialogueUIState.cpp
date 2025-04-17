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
}

void DialogueUIState::Release()
{
}

void DialogueUIState::Update()
{
	if (isSlidingIn)
	{
		dialogueBoxX += 2.0f;
		if (dialogueBoxX >= 25.0f)
		{
			dialogueBoxX = 25.0f;
			isSlidingIn = false;
		}
	}
}

void DialogueUIState::Render(HDC hdc)
{
	if (dialogueBoxImage)
	{
		dialogueBoxImage->RenderScale(
			hdc,
			dialogueBoxX, dialogueBoxY,
			1.0f, 1.0f,
			0.0f,
			false, false,
			0.7f
		);
	}

}

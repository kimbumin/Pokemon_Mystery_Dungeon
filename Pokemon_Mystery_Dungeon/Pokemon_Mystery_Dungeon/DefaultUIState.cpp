#include "DefaultUIState.h"
#include "ImageGDIPlusManager.h"
HRESULT DefaultUIState::Init()
{
	defaultBoxImage = ImageGDIPlusManager::GetInstance()->AddImage("defaultBox", L"Image/UIImage/DefaultBoxImage.png", 1, 1);
	return (defaultBoxImage != nullptr) ? S_OK : E_FAIL;
}

void DefaultUIState::Release()
{
}

void DefaultUIState::Update()
{
	
}

void DefaultUIState::Render(HDC hdc)
{
	if (defaultBoxImage)
	{
		defaultBoxImage->RenderScale(
			hdc,
			defaultImageX, defaultImageY,
			1.0f, 1.0f,
			0.0f,
			false, false,
			0.7f
		);
	}
}

DefaultUIState::~DefaultUIState()
{
}

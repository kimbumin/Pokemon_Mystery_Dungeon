#include "DungeonUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIManager.h"

HRESULT DungeonUIState::Init()
{
	// ¿ÃπÃ¡ˆ
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto DungeonInfoBoxImage = manager.AddImage("DungeonInfoBox", L"Image/UIImage/DungeonUIState/DungeonInfoBox.png");
    return S_OK;
}

void DungeonUIState::Release()
{
}

void DungeonUIState::Update()
{
}

void DungeonUIState::Render(HDC hdc)
{
}

DungeonUIState::~DungeonUIState()
{
}

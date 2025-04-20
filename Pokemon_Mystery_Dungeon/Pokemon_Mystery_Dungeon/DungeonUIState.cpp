#include "DungeonUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIManager.h"

HRESULT DungeonUIState::Init()
{
	// 이미지
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto DungeonInfoBoxImage = manager.AddImage("DungeonInfoBox", L"Image/UIImage/DungeonUIState/DungeonInfoBox.png");

	// UI 엘리먼트 생성
	DungeonInfoBox = new UIElementImage();
	DungeonInfoBox->SetImage(DungeonInfoBoxImage);
	DungeonInfoBox->SetLocalPos(25, 10);
	DungeonInfoBox->setAlpha(0.7f);
	DungeonInfoBox->setScale(1.0f, 1.0f);
	DungeonInfoBox->SetParent(this);


	UpdateRealPos();
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
	if (DungeonInfoBox)
		DungeonInfoBox->Render(hdc);
}

DungeonUIState::~DungeonUIState()
{
}

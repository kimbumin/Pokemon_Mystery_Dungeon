#include "DungeonUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIManager.h"

HRESULT DungeonUIState::Init()
{
	// 이미지
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto DungeonInfoBoxImage = manager.AddImage("DungeonInfoBox", L"Image/UIImage/DungeonUIState/DungeonInfoBox.png");
	auto WaterTypeGifImage = manager.AddImage("WaterType", L"Image/UIImage/DungeonUIState/waterType.gif", 1, 1, true);
	auto FireTypeGifImage = manager.AddImage("FireType", L"Image/UIImage/DungeonUIState/fireType.gif", 1, 1, true);


	// UI 엘리먼트 생성
	DungeonInfoBox = new UIElementImage();
	DungeonInfoBox->SetImage(DungeonInfoBoxImage);
	DungeonInfoBox->SetLocalPos(25, 100);
	DungeonInfoBox->setAlpha(0.7f);
	DungeonInfoBox->SetParent(this);

	int parentWidth = DungeonInfoBox->GetImageWidth();

	// 자식 객체 생성 waterType
	WaterType = new UIElementImage();
	WaterType->SetImage(WaterTypeGifImage);
	WaterType->SetLocalPos(parentWidth - 120, OffsetY[0]);
	WaterType->setAlpha(0.5f);
	WaterType->SetSpeed(0.5f);
	WaterType->setScale(0.17f, 0.17f);
	WaterType->SetParent(DungeonInfoBox);

	// 자식 객체 생성 waterTypeText
	WaterTypeText = new UIElementText();
	WaterTypeText->SetText(L"Water Dungeon");
	WaterTypeText->SetLocalPos(50, OffsetY[0] + 20);
	WaterTypeText->SetParent(DungeonInfoBox);

	// 자식 객체 생성 fireType
	FireType = new UIElementImage();
	FireType->SetImage(FireTypeGifImage);
	FireType->SetLocalPos(parentWidth - 120, OffsetY[1]);
	FireType->setAlpha(0.5f);
	FireType->SetSpeed(0.5f);
	FireType->setScale(0.17f, 0.17f);
	FireType->SetParent(DungeonInfoBox);

	// 자식 객체 생성 fireTypeText
	FireTypeText = new UIElementText();
	FireTypeText->SetText(L"Fire Dungeon");
	FireTypeText->SetLocalPos(50, OffsetY[1] + 20);
	FireTypeText->SetParent(DungeonInfoBox);



	UpdateRealPos();
    return S_OK;
}

void DungeonUIState::Release()
{
}

void DungeonUIState::Update()
{
	if (WaterType)
	{
		WaterType->Update();
	}
	if (FireType)
	{
		FireType->Update();
	}

}

void DungeonUIState::Render(HDC hdc)
{
	if (DungeonInfoBox)
	{
		DungeonInfoBox->Render(hdc);
	}

	if (WaterType)
	{
		WaterType->Render(hdc);
	}
	if (FireType)
	{
		FireType->Render(hdc);
	}
}

DungeonUIState::~DungeonUIState()
{
}

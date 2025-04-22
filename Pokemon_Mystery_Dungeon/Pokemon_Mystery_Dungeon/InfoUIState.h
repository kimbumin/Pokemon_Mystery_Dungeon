#pragma once
#include "UIState.h"
#include "ImageGDIPlus.h"
#include "UIElement.h"

class UIElementImage;
class UIElementText;
class InfoUIState : public UIState, public UIElement
{
private:
	UIElementImage* FirstInfoBox = nullptr;
	UIElementImage* SecondInfoBox = nullptr;
	UIElementImage* ThirdInfoBox = nullptr;
	UIElementImage* FourthInfoBox = nullptr;

	UIElementText* NameText = nullptr;
	UIElementText* LevelText = nullptr;
	UIElementText* HPText = nullptr;


	const int InfoBoxPosX = 500;
	const int InfoBoxPosYOffset[4] = { 0,50,100,150 };

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~InfoUIState() override;
	void SetInfoBoxText(int index, const wstring& text);
};


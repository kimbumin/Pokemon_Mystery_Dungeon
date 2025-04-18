#pragma once
#include "UIElement.h"
#include "ImageGDIPlus.h"

class UIElementImage : public UIElement
{
private:
	ImageGDIPlus* image = nullptr;

	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float alpha = 1.0f;
	float angle = 0.0f;

	bool flipX = false;
	bool flipY = false;

public:
	UIElementImage() = default;
	virtual ~UIElementImage() = default;

	void SetImage(ImageGDIPlus* img) { image = img; }

	void setAlpha(float newAlpha) { alpha = newAlpha; }
	void setScale(float newScaleX, float newScaleY) { scaleX = newScaleX; scaleY = newScaleY; }
	void SetAngle(float newAngle) { angle = newAngle; }
	void SetFlip(bool newFlipX, bool newFlipY) { flipX = newFlipX; flipY = newFlipY; }

	void Render(HDC hdc) override;
};


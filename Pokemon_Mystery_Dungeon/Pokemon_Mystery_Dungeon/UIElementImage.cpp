#include "UIElementImage.h"

void UIElementImage::SetSpeed(float speed)
{
	if (image)
	{
		image->SetGifSpeed(speed);
	}
}

void UIElementImage::Render(HDC hdc)
{
	if (!image) return;

	FPOINT pos = GetRealPos();

	image->RenderScale(
		hdc,
		pos.x, pos.y,
		scaleX, scaleY,
		angle,
		flipX, flipY,
		alpha
	);

	for (auto child : children)
	{
		child->Render(hdc);
	}
}

void UIElementImage::Update()
{
	if (image)
	{
		image->Update(TimerManager::GetInstance()->GetDeltaTime());
	}

	UIElement::Update();
}

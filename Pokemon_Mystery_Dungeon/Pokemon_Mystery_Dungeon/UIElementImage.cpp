#include "UIElementImage.h"

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

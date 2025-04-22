#include "ImageGDIPlus.h"
#include "CameraManager.h"

HRESULT ImageGDIPlus::Init(const wchar_t* filePath, int maxFrameX, int maxFrameY, bool asGif)
{
	Release();

	image = new Gdiplus::Image(filePath);

	if (!image || image->GetLastStatus() != Gdiplus::Ok)
	{
		delete image;
		image = nullptr;
		return E_FAIL;
	}

	width = image->GetWidth();
	height = image->GetHeight();
	this->maxFrameX = maxFrameX;
	this->maxFrameY = maxFrameY;
	frameWidth = width / maxFrameX;
	frameHeight = height / maxFrameY;
	currFrameX = currFrameY = 0;

	isGif = asGif;

	if (isGif)
	{
		image->GetFrameDimensionsList(&gifFrameDimension, 1);
		gifFrameCount = image->GetFrameCount(&gifFrameDimension);
		gifCurrentFrame = 0;

		UINT size = image->GetPropertyItemSize(PropertyTagFrameDelay);
		if (size > 0)
		{
			Gdiplus::PropertyItem* pItem = (Gdiplus::PropertyItem*)malloc(size);
			if (image->GetPropertyItem(PropertyTagFrameDelay, size, pItem) == Gdiplus::Ok)
			{
				UINT* delays = (UINT*)pItem->value;
				gifFrameDelay.resize(gifFrameCount);
				for (UINT i = 0; i < gifFrameCount; ++i)
				{
					// GDI+는 1/100초 단위 → ms로 환산
					gifFrameDelay[i] = delays[i] * 10;
					if (gifFrameDelay[i] == 0)
						gifFrameDelay[i] = 100;
				}
			}
			free(pItem);
		}
	}

	return S_OK;
}

void ImageGDIPlus::Release()
{
	if(image)
	{
		delete image;
		image = nullptr;
	}
	isGif = false;
	gifFrameCount = 1;
	gifCurrentFrame = 0;

}

void ImageGDIPlus::SetGifFrame(UINT frame)
{
	if (!image || !isGif || frame >= gifFrameCount) return;
	image->SelectActiveFrame(&gifFrameDimension, frame);
	gifCurrentFrame = frame;
}

UINT ImageGDIPlus::GetGifFrameCount() const
{
	return gifFrameCount;
}



void ImageGDIPlus::Render(HDC hdc, float x, float y, float angle, bool flipX, bool flipY, float alpha)
{
	if (!image)	return;

	if (isGif)
	{
		image->SelectActiveFrame(&gifFrameDimension, gifCurrentFrame);
	}

	Gdiplus::Graphics graphics(hdc);

	// 이미지 보간 설정
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

	Gdiplus::ColorMatrix colorMatrix = {
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, alpha, 0,
		0, 0, 0, 0, 1
	};	// RGB 고정, 투명도만 조절

	// 이미지 속성 객체
	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix);

	Gdiplus::RectF destRect(x, y, (float)width, (float)height);

	graphics.DrawImage(
		image,
		Gdiplus::RectF(x, y, (float)width, (float)height),
		0, 0, (float)width, (float)height,
		Gdiplus::UnitPixel,
		&imageAttributes
	);
}

// 보류
//void ImageGDIPlus::RenderScale(HDC hdc, float x, float y, float alpha)
//{
//	if (!image)	return;
//
//	RECT rect;
//	GetClientRect(g_hWnd, &rect);
//
//	float scaleX = (float)(rect.right - rect.left) / (float)GameViewSize_X;
//	float scaleY = (float)(rect.bottom - rect.top) / (float)GameViewSize_Y;
//
//	RenderScale(hdc, x * scaleX, y * scaleY, scaleX, scaleY, 0.0f, false, false, alpha);
//
//}

void ImageGDIPlus::RenderScale(HDC hdc, float x, float y, float scaleX, float scaleY, float angle, bool flipX, bool flipY, float alpha)
{
	if (!image)	return;

	if (isGif)
	{
		image->SelectActiveFrame(&gifFrameDimension, gifCurrentFrame);
	}

	Gdiplus::Graphics graphics(hdc);

	// 이미지 보간 설정
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
	Gdiplus::ColorMatrix colorMatrix = {
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, alpha, 0,
		0, 0, 0, 0, 1
	};	// RGB 고정, 투명도만 조절

	// 이미지 속성 객체
	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix);

	Gdiplus::RectF destRect(x, y, (float)width * scaleX, (float)height * scaleY);

	graphics.DrawImage(
		image,
		destRect,
		0, 0,
		(float)width, (float)height,
		Gdiplus::UnitPixel,
		&imageAttributes
	);
}

void ImageGDIPlus::RenderFrame(HDC hdc, float x, float y, int frameIndex, float angle, bool flipX, bool flipY, float alpha)
{
	if (!image)	return;

	Gdiplus::Graphics graphics(hdc);

	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
	Gdiplus::ColorMatrix colorMatrix = {
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, alpha, 0,
		0, 0, 0, 0, 1
	};	// RGB 고정, 투명도만 조절

	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix);

	Gdiplus::RectF destRect(x, y, (float)frameWidth, (float)frameHeight);

	currFrameX = frameIndex % maxFrameX;
	currFrameY = frameIndex / maxFrameX;

	graphics.DrawImage(
		image,
		destRect,
		currFrameX * frameWidth, currFrameY * frameHeight,
		(float)frameWidth, (float)frameHeight,
		Gdiplus::UnitPixel,
		&imageAttributes
	);
}

void ImageGDIPlus::RenderFrameScale(HDC hdc, float x, float y, float scaleX, float scaleY, int frameIndex, float angle, bool flipX, bool flipY, float alpha)
{
	if (!image)	return;

	Gdiplus::Graphics graphics(hdc);

	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

	Gdiplus::ColorMatrix colorMatrix = {
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, alpha, 0,
		0, 0, 0, 0, 1
	};	// RGB 고정, 투명도만 조절

	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix);

	Gdiplus::RectF destRect(x, y, (float)frameWidth * scaleX, (float)frameHeight * scaleY);

	currFrameX = frameIndex % maxFrameX;
	currFrameY = frameIndex / maxFrameX;

	graphics.DrawImage(
		image,
		destRect,
		currFrameX * frameWidth, currFrameY * frameHeight,
		(float)frameWidth, (float)frameHeight,
		Gdiplus::UnitPixel,
		&imageAttributes
	);
}

void ImageGDIPlus::RenderLeftToRight(HDC hdc, float x, float y, float percent, float alpha)
{

}

void ImageGDIPlus::Update(float deltaTime)
{
	if (!isGif || gifFrameCount <= 1 || gifFrameDelay.empty()) return;

	gifElapsedTime += deltaTime * 1000.0f * gifSpeedMultiplier;

	if (gifElapsedTime >= gifFrameDelay[gifCurrentFrame])
	{
		gifElapsedTime = 0.0f;
		gifCurrentFrame = (gifCurrentFrame + 1) % gifFrameCount;
	}
}

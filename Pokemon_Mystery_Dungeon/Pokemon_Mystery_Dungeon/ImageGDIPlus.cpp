#include "ImageGDIPlus.h"

HRESULT ImageGDIPlus::Init(const wchar_t* filePath, int maxFrameX, int maxFrameY)
{
	Release();

	image = Gdiplus::Image::FromFile(filePath);

	if (!image || image->GetLastStatus() != Gdiplus::Ok)
	{
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


	return S_OK;
}

void ImageGDIPlus::Release()
{
	if(image)
	{
		delete image;
		image = nullptr;
	}
}

void ImageGDIPlus::Render(HDC hdc, float x, float y, float angle, bool flipX, bool flipY, float alpha)
{
	if (!image)	return;
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
		destRect,
		0, 0,
		(float)width, (float)height,
		Gdiplus::UnitPixel,
		&imageAttributes
	);
}

void ImageGDIPlus::RenderScale(HDC hdc, float x, float y, float scaleX, float scaleY, float angle, bool flipX, bool flipY, float alpha)
{
	if (!image)	return;
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

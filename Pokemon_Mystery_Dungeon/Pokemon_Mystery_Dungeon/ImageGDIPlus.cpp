#include "ImageGDIPlus.h"
#include "CameraManager.h"

HRESULT ImageGDIPlus::Init(const wchar_t* filePath, int maxFrameX, int maxFrameY)
{
	Release();

	image = new Gdiplus::Bitmap(filePath);

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
	
	if (image->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitmap) != Gdiplus::Ok)
	{
		return E_FAIL;
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

	if (hBitmap)
	{
		DeleteObject(hBitmap);
		hBitmap = nullptr;
	}
}

void ImageGDIPlus::RenderBackground(HDC hdc)
{
	if (!hBitmap)	return;
	
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

	RECT cam = CameraManager::GetInstance()->GetViewPos();
	int width = cam.right - cam.left;
	int height = cam.bottom - cam.top;

	BitBlt(
		hdc,
		0, 0,
		width, height,
		memDC,
		cam.left, cam.top,
		SRCCOPY
	);

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);

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

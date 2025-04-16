//#include "ImageGDIPlus.h"
//
//HRESULT ImageGDIPlus::Init(const wchar_t* filePath, int maxFrameX, int maxFrameY)
//{
//	Release();
//
//	image = Gdiplus::Image::FromFile(filePath);
//
//	if (!image || image->GetLastStatus() != Gdiplus::Ok)
//	{
//		image = nullptr;
//		return E_FAIL;
//	}
//
//	width = image->GetWidth();
//	height = image->GetHeight();
//
//	this->maxFrameX = maxFrameX;
//	this->maxFrameY = maxFrameY;
//
//	frameWidth = width / maxFrameX;
//	frameHeight = height / maxFrameY;
//
//	currFrameX = currFrameY = 0;
//
//
//	return E_NOTIMPL;
//}
//
//void ImageGDIPlus::Release()
//{
//	if(image)
//	{
//		delete image;
//		image = nullptr;
//	}
//}
//
//void ImageGDIPlus::Render(HDC hdc, float x, float y, float angle, bool flipX, bool flipY, float alpha)
//{
//}
//
//void ImageGDIPlus::RenderScale(HDC hdc, float x, float y, float scaleX, float scaleY, float angle, bool flipX, bool flipY, float alpha)
//{
//}
//
//void ImageGDIPlus::RenderFrame(HDC hdc, float x, float y, int frameIndex, float angle, bool flipX, bool flipY, float alpha)
//{
//}
//
//void ImageGDIPlus::RenderFrameScale(HDC hdc, float x, float y, float scaleX, float scaleY, int frameIndex, float angle, bool flipX, bool flipY, float alpha)
//{
//}
//
//void ImageGDIPlus::RenderLeftToRight(HDC hdc, float x, float y, float percent, float alpha)
//{
//}

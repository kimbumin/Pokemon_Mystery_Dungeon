#pragma once
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

class ImageGDIPlus
{
public:
	enum IMAGE_LOAD_TYPE
	{
		Resource,	// 프로젝트 자체에 포함 시킬 이미지
		File,		// 외부에서 로드할 이미지
		Empty,		// 자체 생산할 이미지
		End
	};

private:
	Gdiplus::Image* image = nullptr;

	int width = 0;
	int height = 0;
	int maxFrameX = 1;
	int maxFrameY = 1;
	int frameWidth = 0;
	int frameHeight = 0;
	int currFrameX = 0;
	int currFrameY = 0;

public:
	HRESULT Init(const wchar_t* filePath, int maxFrameX, int maxFrameY);
	
	void Release();

	// x좌표, y좌표, 회전각도, x축 반전 여부, y축 반전 여부, 투명도
	void Render(HDC hdc, float x, float y, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x좌표, y좌표, 가로배율, 새로 배율, 회전각도, x축 반전 여부, y축 반전 여부, 투명도
	void RenderScale(HDC hdc, float x, float y, float scaleX, float scaleY, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x좌표, y좌표, 프레임 인덱스, 회전각도, x축 반전 여부, y축 반전 여부, 투명도
	void RenderFrame(HDC hdc, float x, float y, int frameIndex, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x좌표, y좌표, 가로배율, 세로 배율, 프레임 인덱스, 회전각도, x축 반전 여부, y축 반전 여부, 투명도
	void RenderFrameScale(HDC hdc, float x, float y, float scaleX, float scaleY, int frameIndex, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x좌표, y좌표, 어느 비율까지 그릴지 지정(0.0 ~ 1.0), 투명도
	void RenderLeftToRight(HDC hdc, float x, float y, float percent, float alpha = 1.0f);


	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetFrameWidth() const { return frameWidth; }
	inline int GetFrameHeight() const { return frameHeight; }
	inline int GetMaxFrameX() const { return maxFrameX; }
	inline int GetMaxFrameY() const { return maxFrameY; }
	inline int GetCurrFrameX() const { return currFrameX; }
	inline int GetCurrFrameY() const { return currFrameY; }
};


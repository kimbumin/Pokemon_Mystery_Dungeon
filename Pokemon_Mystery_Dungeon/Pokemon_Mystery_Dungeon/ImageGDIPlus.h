#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <gdiplusimaging.h>

#include "config.h"
#pragma comment(lib, "gdiplus.lib")

// 5100은 GIF에서 '프레임 딜레이 정보'를 가져오기 위한 ID임 - 각 프레임이 보여질
// 시간(딜레이)
#define PropertyTagFrameDelay 0x5100

class ImageGDIPlus
{
public:
    enum IMAGE_LOAD_TYPE
    {
        Resource,  // 프로젝트 자체에 포함 시킬 이미지
        File,      // 외부에서 로드할 이미지
        Empty,     // 자체 생산할 이미지
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

    bool isGif = false;
    GUID gifFrameDimension = {};
    UINT gifFrameCount = 1;
    UINT gifCurrentFrame = 0;

    vector<UINT> gifFrameDelay;
    float gifElapsedTime = 0.0f;
    float gifSpeedMultiplier = 3.0f;

public:
    HRESULT Init(const wchar_t* filePath, int maxFrameX, int maxFrameY,
                 bool ifGif = false);

    void Release();

    // x좌표, y좌표, 회전각도, x축 반전 여부, y축 반전 여부, 투명도
    void Render(HDC hdc, float x, float y, float angle = 0.0f,
                bool flipX = false, bool flipY = false, float alpha = 1.0f);

    // 자동 크기 조정? - 보류
    // void RenderScale(HDC hdc, float x, float y, float alpha = 1.0f);

    void RenderScale(HDC hdc, float x, float y, float scaleX, float scaleY,
                     float angle = 0.0f, bool flipX = false, bool flipY = false,
                     float alpha = 1.0f);
    // x좌표, y좌표, 가로배율, 새로 배율, 회전각도, x축 반전 여부, y축 반전
    // 여부, 투명도

    // x좌표, y좌표, 프레임 인덱스, 회전각도, x축 반전 여부, y축 반전 여부,
    // 투명도
    void RenderFrame(HDC hdc, float x, float y, int frameIndex,
                     float angle = 0.0f, bool flipX = false, bool flipY = false,
                     float alpha = 1.0f);

    // x좌표, y좌표, 가로배율, 세로 배율, 프레임 인덱스, 회전각도, x축 반전
    // 여부, y축 반전 여부, 투명도
    void RenderFrameScale(HDC hdc, float x, float y, float scaleX, float scaleY,
                          int frameIndex, float angle = 0.0f,
                          bool flipX = false, bool flipY = false,
                          float alpha = 1.0f);

    // x좌표, y좌표, 어느 비율까지 그릴지 지정(0.0 ~ 1.0), 투명도
    void RenderLeftToRight(HDC hdc, float x, float y, float percent,
                           float alpha = 1.0f);

    void Update(float deltaTime);

    void SetGifFrame(UINT frameIndex);
    UINT GetGifFrameCount() const;

    inline int GetWidth() const
    {
        return width;
    }
    inline int GetHeight() const
    {
        return height;
    }
    inline int GetFrameWidth() const
    {
        return frameWidth;
    }
    inline int GetFrameHeight() const
    {
        return frameHeight;
    }
    inline int GetMaxFrameX() const
    {
        return maxFrameX;
    }
    inline int GetMaxFrameY() const
    {
        return maxFrameY;
    }
    inline int GetCurrFrameX() const
    {
        return currFrameX;
    }
    inline int GetCurrFrameY() const
    {
        return currFrameY;
    }
    void SetGifSpeed(float multiplier)
    {
        gifSpeedMultiplier = multiplier;
    }
};

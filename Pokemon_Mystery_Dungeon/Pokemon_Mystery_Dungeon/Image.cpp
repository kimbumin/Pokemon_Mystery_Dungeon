#include "Image.h"
#include "Camera.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp =
        (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    return S_OK;  // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height,
                    bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP,
                                            width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp =
        (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    imageInfo->maxFrameX = 0;
    imageInfo->maxFrameY = 0;
    imageInfo->frameWidth = 0;
    imageInfo->frameHeight = 0;
    imageInfo->currFrameX = imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;  // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height,
                    int maxFrameX, int maxFrameY, bool isTransparent,
                    COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP,
                                            width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = imageInfo->currFrameY = 0;

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp =
        (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;  // S_OK, E_FAIL
}

void Image::RenderBackground(HDC hdc)
{
    if (!imageInfo || !imageInfo->hMemDC)
        return;

    RECT cam = CameraManager::GetInstance()->GetViewPos();

    int width = cam.right - cam.left;
    int height = cam.bottom - cam.top;

    if (isTransparent)
    {
        GdiTransparentBlt(hdc, 0, 0, width, height, imageInfo->hMemDC, cam.left,
                          cam.top, width, height, transColor);
    }
    else
    {
        BitBlt(hdc, 0, 0, width, height, imageInfo->hMemDC, cam.left, cam.top,
               SRCCOPY);
    }
}

void Image::Render(HDC hdc, int destX, int destY)
{
    if (isTransparent)
    {
        GdiTransparentBlt(hdc, destX, destY, imageInfo->width,
                          imageInfo->height, imageInfo->hMemDC, 0, 0,
                          imageInfo->width, imageInfo->height, transColor);
    }
    else
    {
        BitBlt(hdc,                // 복사 목적지 DC
               destX, destY,       // 복사 목적지 위치
               imageInfo->width,   // 원본에서 복사될 가로크기
               imageInfo->height,  // 원본에서 복사될 세로크기
               imageInfo->hMemDC,  // 원본 DC
               0, 0,               // 원본 복사 시작 위치
               SRCCOPY             // 복사 옵션
        );
    }
}

void Image::Render(HDC hdc, int destX, int destY, int frameIndex, bool isFlip)
{
    imageInfo->currFrameX = frameIndex;

    if (isFlip && isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0, imageInfo->frameWidth,
                   imageInfo->frameHeight, imageInfo->hMemDC,
                   (imageInfo->frameWidth * imageInfo->currFrameX) +
                       (imageInfo->frameWidth - 1),
                   imageInfo->frameHeight * imageInfo->currFrameY,
                   -imageInfo->frameWidth, imageInfo->frameHeight, SRCCOPY);

        GdiTransparentBlt(hdc, destX, destY, imageInfo->frameWidth,
                          imageInfo->frameHeight,

                          imageInfo->hTempDC, 0, 0, imageInfo->frameWidth,
                          imageInfo->frameHeight, transColor);
    }
    else if (isTransparent)
    {
        GdiTransparentBlt(
            hdc, destX, destY, imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hMemDC, imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight, transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, imageInfo->width / 9, imageInfo->height,
               imageInfo->hMemDC, imageInfo->width / 9 * frameIndex, 0,
               SRCCOPY);
    }
}

void Image::FrameRender(HDC hdc, int destX, int destY, int frameX, int frameY,
                        bool isFlip, bool isCenter)
{
    int x = destX;
    int y = destY;
    if (isCenter)
    {
        x = destX - (imageInfo->frameWidth / 2);
        y = destY - (imageInfo->frameHeight / 2);
    }

    imageInfo->currFrameX = frameX;
    imageInfo->currFrameY = frameY;

    if (isFlip && isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0, imageInfo->frameWidth,
                   imageInfo->frameHeight, imageInfo->hMemDC,
                   (imageInfo->frameWidth * imageInfo->currFrameX) +
                       (imageInfo->frameWidth - 1),
                   imageInfo->frameHeight * imageInfo->currFrameY,
                   -imageInfo->frameWidth, imageInfo->frameHeight, SRCCOPY);

        GdiTransparentBlt(hdc, x, y, imageInfo->frameWidth,
                          imageInfo->frameHeight,

                          imageInfo->hTempDC, 0, 0, imageInfo->frameWidth,
                          imageInfo->frameHeight, transColor);
    }
    else if (isTransparent)
    {
        GdiTransparentBlt(
            hdc, x, y, imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hMemDC, imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight, transColor);
    }
    else
    {
        BitBlt(hdc, x, y, imageInfo->frameWidth, imageInfo->frameHeight,
               imageInfo->hMemDC, imageInfo->frameWidth * imageInfo->currFrameX,
               imageInfo->frameHeight * imageInfo->currFrameY, SRCCOPY);
    }
}

void Image::FrameRenderCamera(HDC hdc, int destX, int destY, int frameX,
                              int frameY, bool isFlip, bool isCenter)
{
    RECT cam = CameraManager::GetInstance()->GetViewPos();
    int x = destX - cam.left;
    int y = destY - cam.top;

    if (isCenter)
    {
        x -= imageInfo->frameWidth / 2;
        y -= imageInfo->frameHeight / 2;
    }

    imageInfo->currFrameX = frameX;
    imageInfo->currFrameY = frameY;

    if (isFlip && isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0, imageInfo->frameWidth,
                   imageInfo->frameHeight, imageInfo->hMemDC,
                   (imageInfo->frameWidth * imageInfo->currFrameX) +
                       (imageInfo->frameWidth - 1),
                   imageInfo->frameHeight * imageInfo->currFrameY,
                   -imageInfo->frameWidth, imageInfo->frameHeight, SRCCOPY);

        GdiTransparentBlt(hdc, x, y, imageInfo->frameWidth,
                          imageInfo->frameHeight,

                          imageInfo->hTempDC, 0, 0, imageInfo->frameWidth,
                          imageInfo->frameHeight, transColor);
    }
    else if (isTransparent)
    {
        GdiTransparentBlt(
            hdc, x, y, imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hMemDC, imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight, transColor);
    }
    else
    {
        BitBlt(hdc, x, y, imageInfo->frameWidth, imageInfo->frameHeight,
               imageInfo->hMemDC, imageInfo->frameWidth * imageInfo->currFrameX,
               imageInfo->frameHeight * imageInfo->currFrameY, SRCCOPY);
    }
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
        DeleteObject(imageInfo->hTempBit);
        DeleteDC(imageInfo->hTempDC);

        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        delete imageInfo;
        imageInfo = nullptr;
    }
}

//void Image::RenderWithCamera(HDC hdc, int x, int y)
//{
//    POINT cam = Camera::GetInstance()->GetCameraPos();
//
//
//    this->Render(hdc, x - cam.x, y - cam.y);
//}
//
//void Image::FrameRenderWithCamera(HDC hdc, int x, int y, int frameX, int frameY,int transparent, bool isCenter)
//{
//    POINT cam = Camera::GetInstance()->GetCameraPos();
//
//
//    this->FrameRender(hdc, x - cam.x, y - cam.y, frameX, frameY, transparent,isCenter);
//}

void Image::RenderWithCamera(HDC hdc, int x, int y)
{
    Camera* cam = Camera::GetInstance();
    POINT camPos = cam->GetCameraPos();
    float zoom = cam->GetZoom();  

    int drawX = static_cast<int>((x - camPos.x) * zoom);
    int drawY = static_cast<int>((y - camPos.y) * zoom);
    
    int drawW = static_cast<int>(imageInfo->width * zoom);
    int drawH = static_cast<int>(imageInfo->height * zoom);

    if (isTransparent)
    {
        GdiTransparentBlt(hdc, drawX, drawY, drawW,drawH, 
                          imageInfo->hMemDC, 0, 0, imageInfo->width,
                          imageInfo->height, transColor);
    }
    else
    {
        StretchBlt(hdc, drawX, drawY, drawW, drawH,       
                   imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
                   SRCCOPY);
    }
}

void Image::FrameRenderWithCamera(HDC hdc, int x, int y, int frameX, int frameY,
                                  bool isFlip, bool isCenter)
{
    Camera* cam = Camera::GetInstance();
    POINT camPos = cam->GetCameraPos();
    float zoom = cam->GetZoom();

    int drawX = static_cast<int>((x - camPos.x) * zoom);
    int drawY = static_cast<int>((y - camPos.y) * zoom);

    int srcW = imageInfo->frameWidth;
    int srcH = imageInfo->frameHeight;

    int drawW = static_cast<int>(srcW * zoom);
    int drawH = static_cast<int>(srcH * zoom);

    if (isCenter)
    {
        drawX -= drawW / 2;
        drawY -= drawH / 2;
    }

    if (isFlip)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0, srcW, srcH, imageInfo->hMemDC,
                   (srcW * frameX) + (srcW - 1), srcH * frameY, -srcW, srcH,
                   SRCCOPY);

        GdiTransparentBlt(hdc, drawX, drawY, drawW, drawH, imageInfo->hTempDC,
                          0, 0, srcW, srcH, transColor);
    }
    else
    {
        GdiTransparentBlt(hdc, drawX, drawY, drawW, drawH, imageInfo->hMemDC,
                          srcW * frameX, srcH * frameY, srcW, srcH, transColor);
    }
}



void Image::RenderPartial(HDC hdc, int destX, int destY, int width, int height)
{
    if (!imageInfo || !imageInfo->hMemDC)
        return;

    if (isTransparent)
    {
        GdiTransparentBlt(hdc, destX, destY, width, height, imageInfo->hMemDC,
                          0, 0, width, height, transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, width, height, imageInfo->hMemDC, 0, 0,
               SRCCOPY);
    }
}
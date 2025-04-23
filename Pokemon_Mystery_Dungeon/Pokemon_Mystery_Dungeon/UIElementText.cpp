#include "UIElementText.h"

#include <sstream>

void UIElementText::Render(HDC hdc)
{
    if (fullText.empty())
        return;

    Gdiplus::Graphics graphics(hdc);
    graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

    FPOINT pos = GetRealPos();
    float lineHeight = fontSize + textLine;

    wstring visibleText =
        isTyping ? fullText.substr(0, visibleTextLength) : fullText;

    wstringstream lineStream(visibleText);
    std::wstring currLine;
    int lineIndex = 0;

    while (getline(lineStream, currLine, L'\n'))
    {
        DrawColoredText(graphics, currLine, pos.x,
                        pos.y + (lineHeight * lineIndex));
        lineIndex++;
    }
}

// 실제로 텍스트 그리는건 아니고 친환해서 내부 텍스트로 설정하는거
void UIElementText::RenderDialogue(const wstring& txt,
                                   const map<wstring, wstring>& values)
{
    fullText = txt;
    for (const auto& [key, value] : values)
    {
        wstring placeHolder = L"〈" + key + L"〉";
        size_t pos = fullText.find(placeHolder);
        while (pos != wstring::npos)
        {
            fullText.replace(pos, placeHolder.length(), L"〈" + value + L"〉");
            pos = fullText.find(placeHolder);
        }
    }

    text = fullText;
}

void UIElementText::DrawColoredText(Gdiplus::Graphics& graphics,
                                    const std::wstring& line, float x, float y)
{
    Gdiplus::FontFamily fontFamily(fontName.c_str());
    Gdiplus::Font font(&fontFamily, fontSize, Gdiplus::FontStyleBold,
                       Gdiplus::UnitPixel);

    Gdiplus::SolidBrush defaultBrush((textColor));  // #1C1C84
    Gdiplus::SolidBrush highlightBrush(
        Gdiplus::Color(255, 241, 179, 0));  // #F1B300

    bool inHighlight = false;
    std::wstring segment;
    float drawX = x;

    for (wchar_t ch : line)
    {
        if (ch == L'〈')
        {
            if (!segment.empty())
            {
                Gdiplus::PointF point(drawX, y);
                graphics.DrawString(segment.c_str(), -1, &font, point, nullptr,
                                    &defaultBrush);

                Gdiplus::RectF size;
                graphics.MeasureString(segment.c_str(), -1, &font, point,
                                       nullptr, &size);
                drawX += size.Width;
                segment.clear();
            }
            inHighlight = true;
            continue;
        }
        if (ch == L'〉')
        {
            if (!segment.empty())
            {
                Gdiplus::PointF point(drawX, y);
                graphics.DrawString(segment.c_str(), -1, &font, point, nullptr,
                                    &highlightBrush);

                Gdiplus::RectF size;
                graphics.MeasureString(segment.c_str(), -1, &font, point,
                                       nullptr, &size);
                drawX += size.Width;
                segment.clear();
            }
            inHighlight = false;
            continue;
        }

        segment += ch;
    }

    // 남은 글자 출력
    if (!segment.empty())
    {
        Gdiplus::PointF point(drawX, y);
        Gdiplus::SolidBrush& brush =
            inHighlight ? highlightBrush : defaultBrush;
        graphics.DrawString(segment.c_str(), -1, &font, point, nullptr, &brush);
    }
}

void UIElementText::TypeEffect(const wstring& txt, float interval)
{
    fullText = txt;
    visibleTextLength = 0;
    elapsedTime = 0.0f;
    charInterval = interval;
    isTyping = true;
}

void UIElementText::SkipTyping()
{
    if (isTyping)
    {
        visibleTextLength = fullText.length();
        isTyping = false;
    }
}

void UIElementText::Update(float dt)
{
    if (isTyping && visibleTextLength < static_cast<int>(fullText.length()))
    {
        elapsedTime += dt;
        while (elapsedTime >= charInterval)
        {
            elapsedTime -= charInterval;
            visibleTextLength++;
        }
    }
}

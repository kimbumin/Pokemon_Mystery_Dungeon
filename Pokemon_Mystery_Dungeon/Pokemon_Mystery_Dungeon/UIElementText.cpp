#include "UIElementText.h"

#include <sstream>

void DebugLog(const std::wstring& msg)
{
    OutputDebugStringW((msg + L"\n").c_str());
}

void UIElementText::Render(HDC hdc)
{
    if (fullText.empty())
        return;

    FPOINT pos = GetRealPos();
    float lineHeight = fontSize + textLine;

    wstring visibleText =
        isTyping ? fullText.substr(0, visibleTextLength) : fullText;

    wstringstream lineStream(visibleText);
    wstring currLine;
    int lineIndex = 0;

    while (getline(lineStream, currLine, L'\n'))
    {
        DrawColoredText(hdc, currLine, (int)pos.x,
                        (int)(pos.y + lineHeight * lineIndex));
        lineIndex++;
    }
}

// 실제로 텍스트 그리는건 아니고 친환해서 내부 텍스트로 설정하는거
const std::wstring& UIElementText::RenderDialogue(
    const std::wstring& txt, const std::map<std::wstring, std::wstring>& values)
{
    text = txt;
    for (const auto& [key, value] : values)
    {
        std::wstring placeHolder = L"<" + key + L">";

        std::wstring replacement = L"<";
        replacement += value;
        replacement += L">";

        size_t pos = text.find(placeHolder);
        while (pos != std::wstring::npos)
        {
            text.replace(pos, placeHolder.length(), replacement);
            pos = text.find(placeHolder);
        }
    }

    fullText = text;
    return fullText;
}

void UIElementText::DrawColoredText(HDC hdc,
                                    const std::wstring& line, float x, float y)
{
    LOGFONT lf = {};
    lf.lfHeight = -fontSize;
    wcscpy_s(lf.lfFaceName, fontName.c_str());

    HFONT hFont = CreateFontIndirect(&lf);
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);

    COLORREF normalColor = textColor;

    bool inHighlight = false;
    std::wstring segment;
    float drawX = x;

    for (wchar_t ch : line)
    {
        if (ch == L'<')
        {
            if (!segment.empty())
            {
                SetTextColor(hdc, inHighlight ? highlightColor : normalColor);
                TextOut(hdc, drawX, y, segment.c_str(), segment.length());
                SIZE sz;
                GetTextExtentPoint32(hdc, segment.c_str(), segment.length(),
                                     &sz);
                drawX += sz.cx;
                segment.clear();
            }
            inHighlight = true;
            continue;
        }

        if (ch == L'>')
        {
            if (!segment.empty())
            {
                SetTextColor(hdc, inHighlight ? highlightColor : normalColor);
                TextOut(hdc, drawX, y, segment.c_str(), segment.length());
                SIZE sz;
                GetTextExtentPoint32(hdc, segment.c_str(), segment.length(),
                                     &sz);
                drawX += sz.cx;
                segment.clear();
            }
            inHighlight = false;
            continue;
        }

        segment += ch;
    }

    if (!segment.empty())
    {
        SetTextColor(hdc, inHighlight ? highlightColor : normalColor);
        TextOut(hdc, drawX, y, segment.c_str(), segment.length());
    }

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

void UIElementText::SetText(const std::wstring& txt)
{
    text = txt;
    fullText = txt;
    visibleTextLength = (int)txt.length();
    isTyping = false;
}

void UIElementText::SetTextLine(float line)
{
    textLine = line;
}

void UIElementText::SetFont(int size)
{
    fontSize = size;
}

void UIElementText::SetTextColorRGB(int r, int g, int b)
{
    textColor = RGB(r, g, b);
}

void UIElementText::SetHighlightColorRGB(int r, int g, int b)
{
    highlightColor = RGB(r, g, b);
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
        while (elapsedTime >= charInterval &&
               visibleTextLength < static_cast<int>(fullText.length()))
        {
            elapsedTime -= charInterval;
            visibleTextLength++;
        }
    }

    if (isTyping && visibleTextLength >= static_cast<int>(fullText.length()))
    {
        isTyping = false;
    }

}

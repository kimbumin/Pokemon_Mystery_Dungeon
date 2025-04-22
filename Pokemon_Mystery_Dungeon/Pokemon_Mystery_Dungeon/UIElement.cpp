#include "UIElement.h"

void UIElement::SetParent(UIElement* newParent)
{
    parent = newParent;
    if (parent)
        parent->children.push_back(this);
    UpdateRealPos();
}

void UIElement::UpdateRealPos()
{
    if (parent)
    {
        FPOINT parentPos = parent->GetRealPos();
        realPos.x = parentPos.x + localPos.x;
        realPos.y = parentPos.y + localPos.y;
    }
    else
    {
        realPos = localPos;
    }

    // 재귀 업데이트
    for (UIElement* child : children)
    {
        child->UpdateRealPos();
    }
}

UIElement::~UIElement()
{
    for (auto child : children)
    {
        delete child;
    }
    children.clear();
}

void UIElement::Update()
{
}

void UIElement::Render(HDC hdc)
{
}

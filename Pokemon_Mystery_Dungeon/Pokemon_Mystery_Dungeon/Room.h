#pragma once

struct Room
{
    int x, y, width, height;
    const int collisionPadding = 1;

    int CenterX() const
    {
        return x + width / 2;
    }
    int CenterY() const
    {
        return y + height / 2;
    }

    // 참이면 겹침 Padding 1
    bool Intersects(const Room& other) const
    {
        return x - collisionPadding <
                   other.x + other.width + collisionPadding &&
               x + width + collisionPadding > other.x - collisionPadding &&
               y - collisionPadding <
                   other.y + other.height + collisionPadding &&
               y + height + collisionPadding > other.y - collisionPadding;
    }
};
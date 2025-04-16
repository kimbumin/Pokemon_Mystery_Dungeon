#pragma once

struct Room {
	int x, y, width, height;

	int CenterX() const { return x + width / 2; }
	int CenterY() const { return y + height / 2; }

    //ÂüÀÌ¸é °ãÄ§
    bool Intersects(const Room& other) const {
        return (x <= other.x + other.width && x + width >= other.x &&
            y <= other.y + other.height && y + height >= other.y);
    }

};
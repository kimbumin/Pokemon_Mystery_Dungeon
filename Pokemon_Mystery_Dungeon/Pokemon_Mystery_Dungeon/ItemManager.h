// ItemManager.h
#pragma once
#include "IItem.h"

class ItemManager {
private:
	vector<unique_ptr<IItem>> items;
	int mapWidth, mapHeight;

public:
	ItemManager(int width, int height) : mapWidth(width), mapHeight(height) {}

	void AddItem(unique_ptr<IItem> item);
	void Update();
	void Render(HDC hdc);
};

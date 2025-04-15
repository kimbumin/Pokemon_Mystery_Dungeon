#pragma once
#include "GameObject.h"
#define TILEMAPTOOL_X	1420
#define TILEMAPTOOL_Y	700

#define SAMPLE_TILE_X	21
#define SAMPLE_TILE_Y	24
#define TILE_SIZE	24
#define TILE_SELECT_SIZE 25

// 메인 그리기 공간 정보
#define TILE_X	25
#define TILE_Y	25
typedef struct tagTile
{
	RECT rc;
	int frameX;
	int frameY;
} TILE_INFO;

class Image;
class TinyWoodsScene : public GameObject
{
public:
	virtual HRESULT Init();		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);	

	TinyWoodsScene();
	virtual ~TinyWoodsScene();

private:
	Image* sampleTile;
	RECT rcSampleTile;

	TILE_INFO tileInfo[TILE_X * TILE_Y];
	RECT rcMain;

	POINT selectedTile;
	wchar_t szText[128];
};


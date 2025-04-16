// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

/*
	ì»´íŒŒ?¼ëŸ¬?ì„œ ?´ë‹¹ ì½”ë“œë¥??¤ì— ?•ì˜??ì½”ë“œë¡?ë³€ê²½í•œ?? 
*/
#define WINSIZE_X	800
#define WINSIZE_Y	400

#define TILEMAPTOOL_X	1420
#define TILEMAPTOOL_Y	700
#define SAMPLE_TILE_X	21
#define SAMPLE_TILE_Y	24
#define TILE_SIZE	24
#define TILE_SELECT_SIZE 25

//?˜ì „ ë§??€???¬ê¸° 25?€??* 25?€?? 
#define TILE_X	25
#define TILE_Y	25

#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

// IV => ê°œì²´ê°? EV = ?¸ë ¥ì¹?
#define IV 30
#define EV 20

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

// ?¬ì¼“ëª?ê¸°ë³¸ ?°ì´??
struct PokemonData {
	int idNumber;
	string name;
	int hp, atk, def, spAtk, spDef, speed, sum, average;
	vector<string> types;
};

enum class Direction
{
    SOUTH,      // ³²
    SOUTHEAST,  // ³²µ¿
    EAST,       // µ¿
    NORTHEAST,  // ºÏµ¿
    NORTH,      // ºÏ
    NORTHWEST,  // ºÏ¼­
    WEST,       // ¼­
    SOUTHWEST,  // ³²¼­
    LENGTH,
};

// Æ÷ÄÏ¸ó ¾Ö´Ï¸ŞÀÌ¼Ç Á¾·ùµé
const vector<string> animTypes = { "Attack", "Hurt", "Idle", "Rotate", "Swing", "Walk" };

/*
	extern ?¤ì›Œ??: ë³€?˜ë‚˜ ?¨ìˆ˜ê°€ ?¤ë¥¸ ?Œì¼???•ì˜?˜ì–´ ?ˆë‹¤ ?¼ëŠ”
	?¬ì‹¤???Œë¦¬???¤ì›Œ??
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

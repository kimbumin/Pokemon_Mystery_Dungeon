// config.h

#pragma once
#define _HAS_STD_BYTE 0
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
#include <fstream>
#include <sstream>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

/*
	컴파일러에서 해당 코드를 뒤에 정의된 코드로 변경한다.
*/
#define WINSIZE_X	800
#define WINSIZE_Y	400

#define GameViewSize_X	500
#define GameViewSize_Y	400

#define TILEMAPTOOL_X	1420
#define TILEMAPTOOL_Y	700
#define SAMPLE_TILE_X	21
#define SAMPLE_TILE_Y	24
#define TILE_SIZE	24
#define TILE_SELECT_SIZE 25


//던전 맵 타일 크기 25타일 * 25타일  
#define TILE_X	25
#define TILE_Y	25

#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

// IV => 개체값, EV = 노력치
#define IV 30
#define EV 20

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

// 포켓몬 기본 데이터
struct PokemonData {
	int idNumber;
	string name;
	int hp, atk, def, spAtk, spDef, speed, sum, average;
	vector<string> types;
};

enum class Direction
{
	SOUTH,      // 0,1
	SOUTHEAST,  // 1,1
	EAST,       // 1,0
	NORTHEAST,  // 1,-1
	NORTH,      // 0,-1
	NORTHWEST,  // -1,-1
	WEST,       // -1,0
	SOUTHWEST,  // -1,1
	LENGTH,
};

// 배열의 Index에 Direction 넣어서
constexpr pair<int, int> directionOffsets[8] = {
	{ 0,  1 },  // SOUTH
	{ 1,  1 },  // SOUTHEAST
	{ 1,  0 },  // EAST
	{ 1, -1 },  // NORTHEAST
	{ 0, -1 },  // NORTH
	{-1, -1 },  // NORTHWEST
	{-1,  0 },  // WEST
	{-1,  1 }   // SOUTHWEST
};

// 포켓몬 애니메이션 종류들
const vector<string> animTypes = { "Attack", "Hurt", "Idle", "Rotate", "Swing", "Walk" };

const vector<string> skillElementType =
{
	"Normal", "Fire", "Fighting", "Water", "Flying", "Grass", "Poison", "Electric", "Ground",
	"Psychic", "Rock", "Ice", "Bug", "Dragon", "Ghost"
};

const vector<string> skillAnimType = {"Normal","Special"};
/*
	extern 키워드 : 변수나 함수가 다른 파일에 정의되어 있다 라는
	사실을 알리는 키워드.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

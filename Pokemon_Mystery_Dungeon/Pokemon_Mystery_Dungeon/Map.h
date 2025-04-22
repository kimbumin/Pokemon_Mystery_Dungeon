#pragma once
#include <vector>
#include "CommonFunction.h"
#include "Room.h"
#include "GameObject.h"

enum TileType {
    TILE_WALL,
    TILE_FLOOR,
    TILE_PATH,
    TILE_OUTLINE,
    TYPE_LENGH
};


enum Direction8 {
    DIR_LEFT_TOP,
    DIR_TOP,
    DIR_RIGHT_TOP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_LEFT_BOTTOM,
    DIR_BOTTOM,
    DIR_RIGHT_BOTTOM,
    DIR_COUNT
};

// ¿ÞÀ§, À§, ¿À¸¥ÂÊ, ¿Þ, ¿À, ¿Þ¹Ø,¹Ø,¿À ¼ø¼­
const int dx[DIR_COUNT] = { -1, 0, 1, -1, 1, -1, 0, 1 };
const int dy[DIR_COUNT] = { -1, -1, -1, 0, 0, 1, 1, 1 };

using Pattern = vector<bool>;
using WildPattern = vector<int>;

struct TilePattern {
    Pattern pattern;           
    pair<int, int> tileIndex; 
};

struct WildTilePattern {
    WildPattern pattern;
    pair<int, int> tileIndex;
};
class Image;

class Map : public GameObject {
public:
    Map() {};
    virtual ~Map() {};

    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;


    void Generate();                    
    void Draw(HDC hdc);

    void MiniMapRender(HDC hdc, int drawingX, int drawingY);
    void CreateRoom(const Room& room);
    void ConnectRooms(const Room& a, const Room& b);
    void ClassifyTiles();
    bool InBounds(int x, int y) const;
    bool IsPathOrFloor(int x, int y) const;
    bool MatchPattern(const WildPattern& pattern, const vector<int>& current) const;
    void TileDesign();
    void RandomTileDesign();

    TileType GetTile(int x, int y) const {return tiles[y][x];}
    bool IsFloor(int x, int y) const { return tiles[y][x] == TILE_FLOOR; }
    vector<POINT> GetWallTiles() { return wallTiles; };

    POINT GetStairPos() { return stairPos; }

private:

    TileType tiles[TILE_Y][TILE_X];
    std::vector<Room> rooms;


    Image* tileImage;
    Image* sea1;
    Image* sea2;
    Image* magma1;
    Image* magma2;
    Image* ice1;
    Image* ice2;
    Image* tiniWoods;
    Image* tiniMeadow;



    Image* stairs;

    std::vector<POINT> floorTiles;
    std::vector<POINT> wallTiles;
    std::vector<POINT> pathTiles;


    std::vector<std::vector<std::pair<int, int>>> tileIndex;

    POINT stairPos;

};
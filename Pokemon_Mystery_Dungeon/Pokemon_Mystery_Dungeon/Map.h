#pragma once
#include <vector>
#include "CommonFunction.h"
#include "Room.h"
#include "GameObject.h"

enum TileType {
    TILE_WALL,
    TILE_FLOOR,
    TILE_PATH,
    TYPE_LENGH
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

    void CreateRoom(const Room& room);

    void ConnectRooms(const Room& a, const Room& b);

    void ClassifyTiles();

    TileType GetTile(int x, int y) const {return tiles[y][x];}

    vector<POINT> GetWallTiles() { return wallTiles; };
private:
    TileType tiles[TILE_Y][TILE_X];
    std::vector<Room> rooms;


    Image* sampleTile;
    Image* stairs;

    std::vector<POINT> floorTiles;
    std::vector<POINT> wallTiles;

    POINT stairPos;

};
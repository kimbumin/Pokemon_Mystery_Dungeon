#pragma once
#include <vector>
#include "CommonFunction.h"
#include "Room.h"
#include "GameObject.h"

enum TileType {
    TILE_WALL,
    TILE_FLOOR
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

    TileType GetTile(int x, int y) const;
    const TileType(&GetTiles() const)[TILE_Y][TILE_X];
    //TileType(*GetTiles())[TILE_X];  // 전체 타일 참조
    const std::vector<Room>& GetRooms() const;

private:
    TileType tiles[TILE_Y][TILE_X];
    std::vector<Room> rooms;


    Image* sampleTile;

    std::vector<POINT> floorTiles;
    std::vector<POINT> wallTiles;
};
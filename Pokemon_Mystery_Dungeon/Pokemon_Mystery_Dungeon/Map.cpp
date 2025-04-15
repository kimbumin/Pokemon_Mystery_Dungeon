#include "Map.h"  
#include <algorithm>  
#include "Image.h"


HRESULT Map::Init()
{
    sampleTile = ImageManager::GetInstance()->AddImage(
        "smapleTile", L"Image/SceneImage/TiniWoods3.bmp",
        525, 600, SAMPLE_TILE_X, SAMPLE_TILE_Y,
        true, RGB(255, 0, 255));

    Generate();

    // 타일 정보 분리
    for (int y = 0; y < TILE_Y; ++y) {
        for (int x = 0; x < TILE_X; ++x) {
            if (tiles[y][x] == TILE_FLOOR)
                floorTiles.push_back({ x, y });
            else if (tiles[y][x] == TILE_WALL)
                wallTiles.push_back({ x, y });
        }
    }
    return S_OK;
}

void Map::Release()
{
}

void Map::Update()
{
}

void Map::Render(HDC hdc)
{
    //for (int y = 0; y < TILE_Y; ++y) {
    //    for (int x = 0; x < TILE_X; ++x) {
    //        if (tiles[y][x] == TILE_FLOOR)
    //            sampleTile->FrameRender(hdc, x * TILE_SIZE, y * TILE_SIZE, 13, 1, 0, 1); //이동가능타일 (13,1)
    //        else if (tiles[y][x] == TILE_WALL)
    //            sampleTile->FrameRender(hdc, x * TILE_SIZE, y * TILE_SIZE, 4, 0, 0, 1); //이동 불가타일
    //    }
    //}

    //// 이동가능 타일
    for (const auto& pt : floorTiles) {
        sampleTile->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, 13, 1, 0, 1);
    }

    // 이동불가 타일
    for (const auto& pt : wallTiles) {
        sampleTile->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, 4, 0, 0, 1);
    }
}

void Map::Generate() {  
   std::srand((unsigned int)std::time(nullptr));  

   for (int y = 0; y < TILE_Y; ++y)  
       for (int x = 0; x < TILE_X; ++x)  
           tiles[y][x] = TILE_WALL;  

   rooms.clear();  
   const int MAX_ROOMS = 8;  

   for (int i = 0; i < MAX_ROOMS; ++i) {  
       Room newRoom;  
       newRoom.width = 6 + rand() % 5;  
       newRoom.height = 6 + rand() % 5;  
       newRoom.x = rand() % (TILE_X - newRoom.width - 1);  
       newRoom.y = rand() % (TILE_Y - newRoom.height - 1);  

       bool overlapped = false;  
       for (const auto& r : rooms) {  
           if (newRoom.Intersects(r)) {  
               overlapped = true;  
               break;  
           }  
       }  

       if (!overlapped) {  
           for (int y = newRoom.y; y < newRoom.y + newRoom.height; ++y)  
               for (int x = newRoom.x; x < newRoom.x + newRoom.width; ++x)  
                   tiles[y][x] = TILE_FLOOR;  

           if (!rooms.empty()) {  
               Room& prev = rooms.back();  
               int prevX = prev.CenterX();  
               int prevY = prev.CenterY();  
               int newX = newRoom.CenterX();  
               int newY = newRoom.CenterY();  

               if (rand() % 2) {  
                   for (int x = (std::min)(prevX, newX); x <= (std::max)(prevX, newX); ++x)  
                       tiles[prevY][x] = TILE_FLOOR;  
                   for (int y = (std::min)(prevY, newY); y <= (std::max)(prevY, newY); ++y)  
                       tiles[y][newX] = TILE_FLOOR;  
               }  
               else {  
                   for (int y = (std::min)(prevY, newY); y <= (std::max)(prevY, newY); ++y)  
                       tiles[y][prevX] = TILE_FLOOR;  
                   for (int x = (std::min)(prevX, newX); x <= (std::max)(prevX, newX); ++x)  
                       tiles[newY][x] = TILE_FLOOR;  
               }  
           }  

           rooms.push_back(newRoom);  
       }  
   }  
}  

void Map::Draw(HDC hdc) {  //과정 여기다 할까 생각중
    for (int y = 0; y < TILE_Y; ++y) {
        for (int x = 0; x < TILE_X; ++x) {
            RECT rc = { x * TILE_SIZE, y * TILE_SIZE, (x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE };
            HBRUSH brush = (tiles[y][x] == TILE_FLOOR) ? (HBRUSH)GetStockObject(WHITE_BRUSH) : (HBRUSH)GetStockObject(BLACK_BRUSH);
            FillRect(hdc, &rc, brush);
        }
    }
}  

TileType Map::GetTile(int x, int y) const {  
   return tiles[y][x];  
}  

const TileType(&Map::GetTiles() const)[TILE_Y][TILE_X]{
    return tiles;
}

const std::vector<Room>& Map::GetRooms() const {  
   return rooms;  
}

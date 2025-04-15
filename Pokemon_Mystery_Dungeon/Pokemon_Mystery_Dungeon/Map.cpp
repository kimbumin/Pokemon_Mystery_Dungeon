#include "Map.h"  
#include <cstdlib>  
#include <ctime>  
#include <algorithm>  

Map::Map() {  
   Generate();  
}  

void Map::Generate() {  
   std::srand((unsigned int)std::time(nullptr));  

   for (int y = 0; y < MAP_HEIGHT; ++y)  
       for (int x = 0; x < MAP_WIDTH; ++x)  
           tiles[y][x] = TILE_WALL;  

   rooms.clear();  
   const int MAX_ROOMS = 8;  

   for (int i = 0; i < MAX_ROOMS; ++i) {  
       Room newRoom;  
       newRoom.width = 6 + rand() % 5;  
       newRoom.height = 6 + rand() % 5;  
       newRoom.x = rand() % (MAP_WIDTH - newRoom.width - 1);  
       newRoom.y = rand() % (MAP_HEIGHT - newRoom.height - 1);  

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

void Map::Draw(HDC hdc) {  
   for (int y = 0; y < MAP_HEIGHT; ++y) {  
       for (int x = 0; x < MAP_WIDTH; ++x) {  
           RECT rc = { x * 16, y * 16, (x + 1) * 16, (y + 1) * 16 };  
           HBRUSH brush = (tiles[y][x] == TILE_FLOOR) ? (HBRUSH)GetStockObject(WHITE_BRUSH) : (HBRUSH)GetStockObject(BLACK_BRUSH);  
           FillRect(hdc, &rc, brush);  
       }  
   }  
}  

TileType Map::GetTile(int x, int y) const {  
   return tiles[y][x];  
}  

TileType(*Map::GetTiles())[MAP_WIDTH] {  
   return tiles;  
}  

const std::vector<Room>& Map::GetRooms() const {  
   return rooms;  
}

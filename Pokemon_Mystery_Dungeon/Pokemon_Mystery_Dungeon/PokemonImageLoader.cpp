#include "PokemonImageLoader.h"
#include <sstream>
#include <fstream>
#include <iomanip>


void PokemonImageLoader::Release()
{
    PokemonImageLoader::GetInstance()->ReleaseInstance();
}

void PokemonImageLoader::LoadPokemonAnim(int pokemonId)
{
	string folderPath = "Image/PokemonAnim/" + PokemonIdToString(pokemonId) + "/";
	string csvPath = folderPath + "AnimData.csv";

	ifstream file(csvPath);
	if (!file.is_open()) return;

	string line;
	getline(file, line); // 첫 줄 생략

    while (getline(file, line)) 
    {
        istringstream ss(line);
        string name, widthStr, heightStr, countStr;

        getline(ss, name, ',');
        getline(ss, widthStr, ',');
        getline(ss, heightStr, ',');
        getline(ss, countStr, ',');

        if (name.empty()) 
        {
            continue;
        }

        int frameWidth = stoi(widthStr);
        int frameHeight = stoi(heightStr);
        int frameX = stoi(countStr);
        int frameY = 8; // 방향 8개

        string key = PokemonIdToString(pokemonId) + name;
        string imagePath = folderPath + name + "-Anim.bmp";

        if (find(animTypes.begin(), animTypes.end(), name) == animTypes.end()) 
        {
            continue; 
            // CSV에는 써있는데 필요없는거 거르기
        }

        if (!ImageManager::GetInstance()->FindImage(key)) 
        {
            ImageManager::GetInstance()->AddImage(
                key, (wstring(imagePath.begin(), imagePath.end())).c_str(),
                frameWidth * frameX, frameHeight * frameY, frameX, frameY,
                true, RGB(255, 0, 255)
            );
        }

        loadedImageKeys.insert(key);
    }

}

void PokemonImageLoader::ClearPokemonImage()
{
    for (auto it = loadedImageKeys.begin(); it != loadedImageKeys.end(); ++it)
    {
        ImageManager::GetInstance()->DeleteImage(*it);
    }
    loadedImageKeys.clear();
}

string PokemonImageLoader::PokemonIdToString(int pokemonId)
{
	//char buf[5]; // \0
	//sprintf(buf, "%04d", pokemonId);
	//string result = buf;
	//return result;

	// 너무 옛날 코드라 c++ 스타일로 바꿈
	// It's too old code, so I changed it to c++ style

	// ostringstream -> sstream
	// setw -> iomanip

	ostringstream oss;
	oss << setw(4) << setfill('0') << pokemonId;
	return oss.str();
}

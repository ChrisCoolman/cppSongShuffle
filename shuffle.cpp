#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

void shuffle(std::string playlistFilePath)
{
    std::string line;
    std::string word;

    std::vector<std::string> row;

    std::vector<std::string> songNames;
    std::vector<std::string> artistNames;
    std::vector<std::string> albumNames;

    // read file
    std::ifstream file(playlistFilePath);

    int num = 0;
    while (std::getline(file, line))
    {
        if (num > 0)
        {
            std::stringstream s(line);
            while (std::getline(s, word, ','))
            {
                row.push_back(word);
            }
        }
        num += 1;
    }

    for (int i = 0; i < row.size(); i += 3)
    {
        songNames.push_back(row[i]);
        artistNames.push_back(row[i + 1]);
        albumNames.push_back(row[i + 2]);
    }
    /* print the songs
    for(int i = 0; i < songNames.size(); i+=1) {
        std::cout << songNames[i] << std::endl;
    }

    for(int i = 0; i < artistNames.size(); i+=1) {
        std::cout << artistNames[i] << std::endl;
    }

    for(int i = 0; i < albumNames.size(); i+=1) {
        std::cout << albumNames[i] << std::endl;
    }
    */
    num = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::string> NEWsongNames;
    std::vector<std::string> NEWartistNames;
    std::vector<std::string> NEWalbumNames;
    bool loopVar = true;
    for (int i = 0; i < songNames.size(); i < 0)
    {
        loopVar = true;
        while (loopVar)
        {
            std::uniform_int_distribution<> distrib(0, songNames.size() - 1);
            num = distrib(gen);
            if (NEWsongNames.size() > 0)
            {
                if (artistNames[num] != NEWartistNames[i])
                {
                    NEWsongNames.push_back(songNames[num]);
                    songNames.erase(songNames.begin() + num);
                    NEWartistNames.push_back(artistNames[num]);
                    artistNames.erase(artistNames.begin() + num);
                    NEWalbumNames.push_back(albumNames[num]);
                    albumNames.erase(albumNames.begin() + num);
                    loopVar = false;
                }
            }
            else
            {
                NEWsongNames.push_back(songNames[num]);
                songNames.erase(songNames.begin() + num);
                NEWartistNames.push_back(artistNames[num]);
                artistNames.erase(artistNames.begin() + num);
                NEWalbumNames.push_back(albumNames[num]);
                albumNames.erase(albumNames.begin() + num);
                loopVar = false;
            }
        }
        continue;
    }
    // prints out songs
    for (int i = 0; i < NEWsongNames.size(); i += 1)
    {
        std::cout << i << ". " << NEWsongNames[i] << " - " << NEWartistNames[i] << std::endl;
    }
    file.close();
}
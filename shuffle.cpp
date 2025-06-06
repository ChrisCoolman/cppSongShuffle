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

    num = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::string> NEWsongNames;
    std::vector<std::string> NEWartistNames;
    std::vector<std::string> NEWalbumNames;
    std::vector<std::string> features;
    std::vector<int> charpos;
    std::vector<std::string> NEWfeatures;
    std::vector<int> NEWcharpos;
    bool loopVar = true;
    bool canTrade = true;
    for (int i = 0; i < songNames.size(); i < 0)
    {
        // variables that need to be reset each iteration
        loopVar = true;
        canTrade = true;
        features.clear();
        charpos.clear();

        // while loop will run again and again until it finds a valid spot for a song
        while (loopVar)
        {
            std::uniform_int_distribution<> distrib(0, songNames.size() - 1);
            num = distrib(gen);
            std::cout << "trying " << songNames[num] << std::endl;
            for(int i = 0; i < artistNames.size(); i++) {
                if(artistNames[i] == "&") {
                    charpos.push_back(i);
                }
            }
            for(int i = 0; i < charpos.size(); i++) {
                if(i == 0) {
                    // take from the start to the first feature
                    features.push_back(artistNames[num].substr(0, charpos[i]));
                }
                else if(i == charpos.size() - 1) {
                    // take from the current feature to the end
                    features.push_back(artistNames[num].substr(charpos[i], (charpos.size() - charpos[i])));
                }
                else {
                    // take from the last feature to this feature
                    features.push_back(artistNames[num].substr(charpos[i], charpos[i + 1]));
                }
            }
            for(int i = 0; i < NEWartistNames.size(); i++) {
                if(NEWartistNames[i] == "&") {
                    NEWcharpos.push_back(i);
                }
            }
            for(int i = 0; i < NEWcharpos.size(); i++) {
                if(i == 0) {
                    // take from the start to the first feature
                    NEWfeatures.push_back(NEWartistNames[num].substr(0, NEWcharpos[i]));
                }
                else if(i == NEWcharpos.size() - 1) {
                    // take from the current feature to the end
                    NEWfeatures.push_back(NEWartistNames[num].substr(NEWcharpos[i], (NEWcharpos.size() - NEWcharpos[i])));
                }
                else {
                    // take from the last feature to this feature
                    NEWfeatures.push_back(NEWartistNames[num].substr(NEWcharpos[i], NEWcharpos[i + 1]));
                }
            }
            if (NEWsongNames.size() > 0)
            {
                for(int i = 0; i < features.size(); i++) {
                    for(int k = 0; k < NEWfeatures.size(); k++) {
                        if(NEWfeatures[k] == features[i]) {
                            canTrade = false;
                        }
                    }
                }
                if(artistNames[num - 1] == NEWartistNames[i]) {
                    canTrade = false;
                }
                if (canTrade)
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

    for (int i = 0; i < charpos.size(); i += 1)
    {
        std::cout << charpos[i] << std::endl;
    }
    file.close();
}
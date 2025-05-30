#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <vector>

void shuffle(std::string playlistFilePath) {
    std::string line;
    std::string word;

    std::vector<std::string> row;

    std::vector<std::string> songNames;
    std::vector<std::string> ArtistNames;
    std::vector<std::string> AlbumNames;

    // read file
    std::ifstream file(playlistFilePath);

    int num = 0;
    while(std::getline(file, line)) {
        if(num > 0) {
            std::stringstream s(line);
            while(std::getline(s, word, ',')) {
                row.push_back(word);
            }
        }
        num+=1;
    }

    for(int i = 0; i < row.size(); i+=3) {
        songNames.push_back(row[i]);
        ArtistNames.push_back(row[i + 1]);
        AlbumNames.push_back(row[i + 2]);
    }
    /* print the songs
    for(int i = 0; i < songNames.size(); i+=1) {
        std::cout << songNames[i] << std::endl;
    }

    for(int i = 0; i < ArtistNames.size(); i+=1) {
        std::cout << ArtistNames[i] << std::endl;
    }

    for(int i = 0; i < AlbumNames.size(); i+=1) {
        std::cout << AlbumNames[i] << std::endl;
    }
    */
    int min = 0;
    int max = songNames.size() - 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    int randomNumber;
    num = -1;
    
    for(int i = 0; i < songNames.size(); i+=1) {
        while(num > -1 && ArtistNames[num] != ArtistNames[i]) {
            std::uniform_int_distribution<> distrib(min, max);
            num = distrib(gen);
            std::string temp = songNames[i];
            songNames.erase(songNames.begin() + i);
            songNames.insert(songNames.begin() + num, temp);
        }
    }
    for(int i = 0; i < songNames.size(); i+=1) {
        std::cout << songNames[i] << std::endl;
    }

    file.close();
}
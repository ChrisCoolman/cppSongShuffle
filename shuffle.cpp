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
    std::vector<std::string> artistNames;
    std::vector<std::string> albumNames;

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
    int min = 0;
    int max = songNames.size() - 1;
    num = 0;
    bool cool;
    for(int i = 0; i < songNames.size(); i++) {
        cool = true;
        int maxAttempts = 3;
        int attempts = 0;

        while (cool && attempts < maxAttempts) {
            std::cout << attempts << std::endl;
            std::cout << songNames[i] << std::endl;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(min, max);
            num = distrib(gen);
            bool sameArtist = true;
            bool sameAlbum = true;
            if(artistNames[i] != artistNames[num]) {
                sameArtist = false;
            }
            if(artistNames.size() > num + 1) {
                if(artistNames[i] != artistNames[num + 1]) {
                    sameArtist = false;
                }
            }
            if(num > 0) {
                if(artistNames[i] != artistNames[num - 1]) {
                    sameArtist = false;
                }
            }
            if(albumNames[i] != albumNames[num]) {
                sameAlbum = false;
            }
            if(albumNames.size() > num + 1) {
                if(albumNames[i] != albumNames[num + 1]) {
                    sameAlbum = false;
                }
            }
            if(num > 0) {
                if(albumNames[i] != albumNames[num - 1]) {
                    sameAlbum = false;
                }
            }
            std::cout << sameArtist << " <- artist - album -> " << sameAlbum << std::endl;
            if(sameArtist == false && sameAlbum == false) {
                std::string temp = songNames[i];
                std::string replacement = songNames[num];
                songNames.erase(songNames.begin() + i);
                songNames.insert(songNames.begin() + i, replacement);
                songNames.insert(songNames.begin() + num, temp);
                temp = artistNames[i];
                replacement = artistNames[num];
                artistNames.erase(artistNames.begin() + i);
                artistNames.insert(artistNames.begin() + i, replacement);
                artistNames.insert(artistNames.begin() + num, temp);
                cool = false;
            }
            else {
                continue;
            }
        }
    }
    file.close();
}
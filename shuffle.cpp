#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    std::vector<std::string> NEWsongNames;
    for(int i = 0; i < songNames.size(); i < 0) {
        bool cool = false;
        while(cool) {
            num = distrib(gen);
            // put better code here
        }
        num = distrib(gen);
        // I formely apologize for how bad this code right here it
        if(songNames[num] != "") {
            NEWsongNames.push_back(songNames[num]);
            songNames.erase(songNames.begin() + num);
        }
        else {
            num = distrib(gen);
            if(songNames[num] != "") {
            NEWsongNames.push_back(songNames[num]);
            songNames.erase(songNames.begin() + num);
            }
            else {
                num = distrib(gen);
                NEWsongNames.push_back(songNames[num]);
            songNames.erase(songNames.begin() + num);
            }
        }
    }
    for(int i = 0; i < NEWsongNames.size(); i+=1) {
        std::cout << NEWsongNames[i] << std::endl;
    }
    file.close();
}
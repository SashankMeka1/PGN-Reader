#include "reader.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <ctype.h>

using namespace std;

PGNReader::PGNReader() {
    ifstream inFile;
    inFile.open("params.txt");
    string paramName;
    for (int paramNum = 0; getline(inFile, paramName); paramNum++) {
        
        PARAM_MAP[paramName] = paramNum;
        
    }
}

vector<Game> PGNReader::readPGN() {
    vector<Game> gameList;
    
    
    
    for (const auto& entry: std::filesystem::directory_iterator(GAME_PATH)) {
        string path = entry.path().string();
        if (path.substr(path.find_last_of("."), string::npos) == ".pgn") {
            getMoves(path, gameList);
        }
        
        
    }

    return gameList;
}

void PGNReader::getMoves(string path, vector<Game>& gameList) {
   
    ifstream inFile;
    inFile.open(path);
    
    if (inFile.is_open()) {
        
        string gameArr[Game::NUM_PARAMS];
        
        
        string line;
        bool gameOver = false;

        

        cout << endl << "File Opened" << endl << endl;
        while (getline(inFile, line)) {
          
           
            
           if (!line.empty()) {
                int first = 0;
                
                for (; first != line.size() && line.at(first) != '"'; first++) {} 
                
                                
                
                if (first == line.size()) {
                    
                    gameOver = true; 
                    gameArr[Game::NUM_PARAMS - 1] += line + " ";
                    
                } else {
                    int len = line.size() - 3 - first;
                    string paramName = line.substr(1, first);
                    int paramIndex = PARAM_MAP[paramName];
                      
                    gameArr[paramIndex] = line.substr(first + 1, len);
                    if (paramIndex == 0) {
                        cout << gameArr[paramIndex];
                    }
                    //cout << gameArr[paramIndex]; 
                }
                

           } else if (gameOver) {
                gameOver = false;
                
                
                gameArr[Game::NUM_PARAMS - 1] = "";
                gameList.push_back(Game(gameArr));
                
           }


            
        }
        
        inFile.close();
        
    }
}

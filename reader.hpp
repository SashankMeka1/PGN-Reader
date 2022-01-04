#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include "game.hpp"
#include <map>


using namespace std;

class PGNReader {
    private:
        string GAME_PATH = "games/";
        void getMoves(string path, vector<Game>& gameList);
       
    public:
        PGNReader();
        vector<Game> readPGN();
        inline static map<string, int> PARAM_MAP = map<string, int>();
        
};

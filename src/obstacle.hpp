#pragma once
#include "raylib.h"
#include "block.hpp"
#include<vector>

class Obstacle{ 
    public:
        Obstacle(Vector2 position);
        void Draw();
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
    private: 
    Vector2 position;


};
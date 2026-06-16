#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
class Game{ 
    public: 
        Game(); 
        ~Game();
        void Draw(); 
        void UpdatePos();
        void HandleInput();
        void DeleteInactiveBullets();
    private: 
    std::vector<Obstacle> CreateObstacles();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
};
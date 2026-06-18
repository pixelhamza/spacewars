#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include<memory>
#include<vector>
#include<map> 

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
    std::vector<std::unique_ptr<Alien>> CreateAliens();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
 
    std::vector<std::unique_ptr<Alien>> aliens;
    std::map<AlienType,Texture2D> alienTextures;

    void MoveAliens();
    void DropAliens();
    float alienSpeed = 0.5f;
    int alienDirection = 1; //1 right -1 left
};
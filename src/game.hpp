#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "bullet.hpp"
#include "mysteryship.hpp"
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
        void CheckCollisions();
    private: 
    std::vector<Obstacle> CreateObstacles();
    std::vector<std::unique_ptr<Alien>> CreateAliens();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Bullet> alienLasers;
 
    std::vector<std::unique_ptr<Alien>> aliens;
    std::map<AlienType,Texture2D> alienTextures;

    void MoveAliens();
    void DropAliens();
    void AlienShootLaser();
    float alienSpeed = 0.5f;
    int alienDirection = 1; //1 right -1 left
    constexpr static float alienLaserShootInterval = 0.50;
    float lastTimeAlienFired;


    std::unique_ptr<MysteryShip> mysteryShip = nullptr;
    Texture2D mysteryShipTexture;
    float lastMysteryShipSpawn = 0.0f;
    float mysteryShipSpawnInterval = 30.0;

    void UpdateMysteryShip();
    void SpawnMysteryShip();
};
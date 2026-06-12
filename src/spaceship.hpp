#pragma once
#include "raylib.h"
#include "bullet.hpp"
#include<vector>

class Spaceship{
    public : 
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void ShootLaser();
        float GetHeight() const;
        float GetWidth() const ;
        std::vector<Bullet> bullets;
    private: 
        Texture2D spaceshipSprite;
        Vector2 position;
        Vector2 velocity;
        float scale ;




};
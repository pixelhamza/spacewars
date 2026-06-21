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
        bool ShootBullet();
        float GetHeight() const;
        float GetWidth() const ;
        Rectangle GetRect() const;
        std::vector<Bullet> bullets;
        void Respawn();
        bool IsAlive();
        void Death();
        Vector2 GetPos();
        
    private: 
        Texture2D spaceshipSprite;
        Vector2 position;
        Vector2 velocity;
        double lastFireTime;
        bool alive;






};
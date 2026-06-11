#pragma once
#include "raylib.h"

class Spaceship{
    public : 
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void ShootLaser();
    private: 
        Texture2D spaceshipSprite;
        Vector2 position;
        float scale ;




};
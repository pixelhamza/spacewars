#pragma once
#include "raylib.h"

class Bullet{ 
    public: 
        Bullet(Vector2 position,float speed); 
        void Draw();
        void Update();

    private: 
        Vector2 position; 
        float speed;
        bool active;
};
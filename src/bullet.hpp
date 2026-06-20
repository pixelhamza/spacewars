#pragma once
#include "raylib.h"

class Bullet{ 
    public: 
        Bullet(Vector2 position,float speed); 
        void Draw();
        void Update();
        bool active;
        Rectangle GetRect()const;

    private: 
        Vector2 position; 
        float speed;
};
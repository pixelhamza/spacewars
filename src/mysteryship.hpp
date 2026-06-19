#pragma once
#include "raylib.h"

class MysteryShip{
    public:
        MysteryShip(Vector2 position,Texture2D image);
        void Update();
        void Draw();
        bool IsActive() const; 
        void Deactivate();
        Vector2 GetPosition() const;
    private:
        Vector2 position; 
        Texture2D image;
        bool active = true;
        float speed = 3.0f;
};
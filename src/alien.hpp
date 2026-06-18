#pragma once
#include "raylib.h"
#include<map> 

enum class AlienType{Squid = 1, Crab , Octopus};

class Alien {
    public: 
        Alien(Vector2 position,AlienType type,const std::map<AlienType,Texture2D>&textures);
        void Update(float dx, float dy); 
        void Draw(); 
        bool IsAlive() const;
        void Kill();
        Vector2 GetPosition() const;
    private: 
        Vector2 position;
        AlienType type;
        Texture2D image;
        bool alive = true; 
};

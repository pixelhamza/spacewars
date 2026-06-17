#pragma once
#include "raylib.h"
#include<map> 

enum class AlienType{Squid = 1, Crab , Octopus};

class Alien {
    public: 
        Alien(Vector2 position,AlienType type,const std::map<AlienType,Texture2D>&textures);
        void Update(); 
        void Draw(); 
        AlienType GetType() const;
        Texture2D alienSprite; 
    private: 
        Vector2 position;
        AlienType type;
        Texture2D image;
};

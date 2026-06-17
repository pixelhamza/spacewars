#include "alien.hpp"

Alien::Alien(Vector2 position,AlienType type,
    const std::map<AlienType,Texture2D>&textures){  
    this->type = type;
    this->position = position;
    this->image = textures.at(type);
}

void Alien::Draw(){ 
    DrawTextureV(image,position,WHITE);
}
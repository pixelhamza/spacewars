#include "alien.hpp"

Alien::Alien(Vector2 position,AlienType type,
    const std::map<AlienType,Texture2D>&textures){  
    this->type = type;
    this->position = position;
    this->image = textures.at(type);
}

void Alien::Draw(){ 
    if(alive) DrawTextureV(image,position,WHITE);
}

void Alien::Update(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}
Vector2 Alien::GetPosition() const {
    return position;
}

bool Alien::IsAlive() const {
    return alive;
}

void Alien::Kill() {
    alive = false;
}

Rectangle Alien :: GetRect() const{
    return Rectangle{position.x,position.y,(float)image.width,(float)image.height};
}
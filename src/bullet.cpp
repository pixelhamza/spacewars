#include "bullet.hpp"

Bullet::Bullet(Vector2 position,float speed){
    this->speed = speed; 
    this->position = position;
}

void Bullet::Draw(){
    DrawRectangle(position.x - 2, position.y - 2, 8, 20, Fade(YELLOW, 0.3f));
    DrawRectangleGradientV(position.x, position.y, 4, 16, WHITE, YELLOW);
}

void Bullet::Update(){ 
    position.y+= speed ;
}

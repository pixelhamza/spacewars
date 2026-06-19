#include "mysteryship.hpp"

MysteryShip::MysteryShip(Vector2 position,Texture2D image){
    this->position = position;
    this->image = image;
}
void MysteryShip::Draw(){
    if(active) DrawTextureV(image,position,WHITE);
}
void MysteryShip::Update(){
    position.x += speed;
    if(position.x>GetScreenWidth()){
        active = false;
    }
}

bool MysteryShip::IsActive() const { return active; }
void MysteryShip::Deactivate() { active = false; }
Vector2 MysteryShip::GetPosition() const { return position; }
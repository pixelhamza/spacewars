#include "spaceship.hpp"

Spaceship::Spaceship(){
    spaceshipSprite = LoadTexture("assets/texture/spaceship.png");
    scale = 0.25f; 
    position.x = (GetScreenWidth() - spaceshipSprite.width * scale) / 2.0f;
    position.y = GetScreenHeight() - spaceshipSprite.height * scale -15;

}

Spaceship::~Spaceship(){ 
    UnloadTexture(spaceshipSprite);
}

void Spaceship::Draw(){

    DrawTextureEx(
        spaceshipSprite,
        position,
        0.0f,
        scale, 
        WHITE
    ); 
}
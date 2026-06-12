#include "spaceship.hpp"
#define SHOOT_INTERVAL 0.35
Spaceship::Spaceship(){
    spaceshipSprite = LoadTexture("assets/texture/spaceship.png");
    scale = 0.25f; 
    position.x = (GetScreenWidth() - spaceshipSprite.width * scale) / 2.0f;
    position.y = GetScreenHeight() - spaceshipSprite.height * scale -15;
    velocity.x = 7; 
    velocity.y = 0;
    lastFireTime = 0.0;

}

Spaceship::~Spaceship(){ 
    UnloadTexture(spaceshipSprite);
} 

float Spaceship::GetWidth() const
{
    return spaceshipSprite.width * scale;
}

float Spaceship::GetHeight() const
{
    return spaceshipSprite.height * scale;
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
void Spaceship::MoveLeft(){
    position.x-=velocity.x;
    if(position.x<0)position.x = 0;
}

void Spaceship::MoveRight(){
    position.x+=velocity.x;

    if(position.x + GetWidth()>GetScreenWidth()){
        position.x = GetScreenWidth() - GetWidth();
    }
}

void Spaceship::ShootBullet(){
    if(GetTime() - lastFireTime >= SHOOT_INTERVAL){
    bullets.push_back(Bullet({position.x + GetWidth()/2 -2,position.y},-7));
    lastFireTime = GetTime();
    }

}


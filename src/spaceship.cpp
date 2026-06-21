#include "spaceship.hpp"
#define SHOOT_INTERVAL 0.35
#define INITIAL_POSITION_X (GetScreenWidth() - spaceshipSprite.width) / 2.0f;
#define INITIAL_POSITION_Y GetScreenHeight() - spaceshipSprite.height -15;
Spaceship::Spaceship(){
    spaceshipSprite = LoadTexture("assets/texture/spaceship.png");
    position.x =  INITIAL_POSITION_X;
    position.y = INITIAL_POSITION_Y;
    velocity.x = 7; 
    velocity.y = 0;
    lastFireTime = 0.0;
    alive = true ;

}

Spaceship::~Spaceship(){ 
    UnloadTexture(spaceshipSprite);
} 

float Spaceship::GetWidth() const
{
    return spaceshipSprite.width;
}

float Spaceship::GetHeight() const
{
    return spaceshipSprite.height;
}

void Spaceship::Draw(){
    if(alive) DrawTextureV(spaceshipSprite,position,WHITE);
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
    if(alive){
        if(GetTime() - lastFireTime >= SHOOT_INTERVAL){
        bullets.push_back(Bullet({position.x + GetWidth()/2 -2,position.y},-7));
        lastFireTime = GetTime();
        }
    }

}
Rectangle Spaceship::GetRect() const {
    return Rectangle{position.x,position.y,float(spaceshipSprite.width),(float)spaceshipSprite.height};
}

void Spaceship::Respawn(){
    alive = true;
    position.x = INITIAL_POSITION_X;
    position.y = INITIAL_POSITION_Y;

}
bool Spaceship::IsAlive(){
    return alive;
}
void Spaceship::Death(){
    alive = false;
}
Vector2 Spaceship:: GetPos(){
    return position;
}


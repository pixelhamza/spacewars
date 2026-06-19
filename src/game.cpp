#include "game.hpp"
#include<iostream>


Game::Game(){
    obstacles = CreateObstacles(); 
    alienTextures[AlienType::Crab] = LoadTexture("assets/texture/crab.png");
    alienTextures[AlienType::Octopus] = LoadTexture("assets/texture/octopus.png");
    alienTextures[AlienType::Squid] = LoadTexture("assets/texture/squid.png");

    aliens = CreateAliens();
    lastTimeAlienFired = 0;



}

Game::~Game(){
    for(auto &[type, texture] : alienTextures){
        UnloadTexture(texture);
    }
}


void Game::UpdatePos(){ 
    for(auto &bullet: spaceship.bullets){ 
        bullet.Update();

    }
    for(auto &bullet: alienLasers){
        bullet.Update();
    }
    DeleteInactiveBullets();

    AlienShootLaser();
    MoveAliens();

}
void Game:: Draw(){ 
    spaceship.Draw();

    for(auto &bullet  : spaceship.bullets){ 
        bullet.Draw();

    }

    for(auto &obstacle : obstacles) obstacle.Draw();

    for(auto &alien : aliens) alien->Draw();
    for(auto &alienBullet : alienLasers) alienBullet.Draw();
}

void Game::HandleInput(){ 
    if(IsKeyDown(KEY_LEFT)) spaceship.MoveLeft();
    else if(IsKeyDown(KEY_RIGHT)) spaceship.MoveRight();
    else if(IsKeyDown(KEY_SPACE))spaceship.ShootBullet();

}

void Game::DeleteInactiveBullets(){ 
    for(auto it=spaceship.bullets.begin();it!=spaceship.bullets.end();){ 
        if(!it->active){ 
           it = spaceship.bullets.erase(it);
        }
        else ++it;
    }

    for(auto it = alienLasers.begin();it!=alienLasers.end();){
        if(!it->active){
            it = alienLasers.erase(it);
        }
        else ++it;
    }
}

std::vector<Obstacle> Game::CreateObstacles(){
    int obstacle_width = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (3 * obstacle_width)) / 4;

    for (size_t i{}; i <3 ; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacle_width;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 150)}));

    }
    return obstacles;
    
}

std::vector<std::unique_ptr<Alien>> Game::CreateAliens(){ 
    std::vector<std::unique_ptr<Alien>> aliens;

    for(size_t row{};row< 5;row++){
        AlienType type;
        if(row==0) type = AlienType::Squid;
        else if(row<=2)type = AlienType::Crab;
        else type = AlienType::Octopus;

        for(size_t col{};col<11;col++){ 
            Vector2 pos = {75.0f + col * 55.0f,50.0f+ row*55.0f};
            aliens.push_back(std::make_unique<Alien>(pos,type,alienTextures));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for (auto& alien : aliens) {
        if (!alien->IsAlive()) continue;

        if (alien->GetPosition().x + 48 >= GetScreenWidth() && alienDirection == 1) {
            alienDirection = -1;
            DropAliens();
            break;
        }
        if (alien->GetPosition().x <= 0 && alienDirection == -1) {
            alienDirection = 1;
            DropAliens();
            break;
        }
    }

    for (auto& alien : aliens) {
        if (alien->IsAlive()) alien->Update(alienDirection * alienSpeed, 0);
    }
}

void Game::DropAliens() {
    for (auto& alien : aliens) {
        if (alien->IsAlive()) alien->Update(0, 4);
    }
}

void Game::AlienShootLaser(){ 

    double curr_time = GetTime();
    if(curr_time - lastTimeAlienFired >= alienLaserShootInterval && !aliens.empty()){
        int random_index = GetRandomValue(0, static_cast<int>(aliens.size()) - 1);
        size_t idx = static_cast<size_t>(random_index);
        if (aliens[idx] && aliens[idx]->IsAlive()) {
            Vector2 alienPos = aliens[idx]->GetPosition();
            Vector2 laserPos = {alienPos.x + 24, alienPos.y + 48};
            alienLasers.push_back(Bullet(laserPos,6));

        }
        lastTimeAlienFired = GetTime();
    }
}
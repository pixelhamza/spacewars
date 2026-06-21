#include "game.hpp"
#include<iostream>


Game::Game(){
    obstacles = CreateObstacles(); 
    alienTextures[AlienType::Crab] = LoadTexture("assets/texture/crab.png");
    alienTextures[AlienType::Octopus] = LoadTexture("assets/texture/octopus.png");
    alienTextures[AlienType::Squid] = LoadTexture("assets/texture/squid.png");
    mysteryShipTexture = LoadTexture("assets/texture/mystery.png");
    aliens = CreateAliens();
    lastTimeAlienFired = 0;



}

Game::~Game(){
    for(auto &[type, texture] : alienTextures){
        UnloadTexture(texture);
    }
    UnloadTexture(mysteryShipTexture);
}


void Game::UpdatePos(){ 
    if(state == GameState::GameOver)return;

    for(auto &bullet: spaceship.bullets){ 
        bullet.Update();

    }
    for(auto &bullet: alienLasers){
        bullet.Update();
    }
    DeleteInactiveBullets();

    AlienShootLaser();
    MoveAliens();
    CheckCollisions();
    UpdateMysteryShip();
    ShipRespawn();
    UpdateDifficulty();
    

}
void Game:: Draw(){ 
    if(state == GameState::GameOver){
        DrawGameOver();
        return;
    }
    DrawScoreUI();
    spaceship.Draw();

    for(auto &bullet  : spaceship.bullets){ 
        bullet.Draw();

    }

    for(auto &obstacle : obstacles) obstacle.Draw();

    for(auto &alien : aliens) alien->Draw();
    for(auto &alienBullet : alienLasers) alienBullet.Draw();
    if(mysteryShip)mysteryShip->Draw();
}

void Game::DrawGameOver(){
    DrawText("GAME OVER", GetScreenWidth()/2 - 150, 280, 60, RED);
    //TODO: GAME OVER SCREEN DESIGNING
}

void Game::ResetGame(){
    aliens = CreateAliens();
    obstacles = CreateObstacles();
    spaceship.Respawn();
    score = 0;
    lives = 3;
    spaceship.bullets.clear();
    alienLasers.clear();
    alienDirection = 1;
    mysteryShip.reset();           
    lastMysteryShipSpawn = GetTime();
    state = GameState::Playing;

    
}

void Game::HandleInput(){ 
    if(state == GameState::GameOver){
        if(IsKeyPressed(KEY_ENTER)){
            ResetGame();
        }
        return;
    }
    if(!spaceship.IsAlive())return;
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

void Game::UpdateMysteryShip() {
    double curr_time = GetTime();
    if (!mysteryShip && curr_time - lastMysteryShipSpawn >= mysteryShipSpawnInterval) {
        SpawnMysteryShip();
        lastMysteryShipSpawn = GetTime();
    }

    if (mysteryShip) {
        mysteryShip->Update();
        if (!mysteryShip->IsActive()) {
            mysteryShip.reset();
        }
    }
}

void Game::SpawnMysteryShip() {
    mysteryShip = std::make_unique<MysteryShip>(Vector2{0, 30}, mysteryShipTexture);
}

void Game::CheckCollisions(){
    for(auto &bullet:spaceship.bullets){
        if(!bullet.active)continue;
        //spaceshipbullet-obstacle collision
        for (auto& obstacle : obstacles) {
            for (auto& block : obstacle.blocks) {
                if (!block.active) continue;
                if (CheckCollisionRecs(bullet.GetRect(), block.GetRect())) {
                    block.active = false;
                    bullet.active = false;
                    break;
                }
            }
        }
        //bullet-alien collision 
        for(auto &alien : aliens){
            if(!alien->IsAlive())continue;
             
            
            if(CheckCollisionRecs(bullet.GetRect(),alien->GetRect())){
                score +=alien->GetScoreValue();
                alien->Kill();
                bullet.active = false;
                break;

            }
        }
        //spaceship-mysteryship collision
        if(mysteryShip && CheckCollisionRecs(mysteryShip->GetRect(),bullet.GetRect())){
            score+=mysteryShip->GetScoreValue();
            bullet.active = false;
            mysteryShip->Deactivate();
        } 
    }

     for(auto &bullet:alienLasers){
        if(!bullet.active)continue;
        if(!spaceship.IsAlive())continue;
            //alienbullet to obstacle collision
            for (auto& obstacle : obstacles) {
                for (auto& block : obstacle.blocks) {
                    if (!block.active) continue;
                    if (CheckCollisionRecs(bullet.GetRect(), block.GetRect())) {
                        block.active = false;
                        bullet.active = false;
                        break;
                    }
                }
            }
        //spaceship-bullet collision
        if(CheckCollisionRecs(bullet.GetRect(),spaceship.GetRect())){
            std::cout<<"Ship hit\n";
            bullet.active = false;
            spaceship.Death();
            lives--;
            if(lives<=0)state=GameState::GameOver;//GameOver
            break;
        }

    }
}

void Game::ShipRespawn(){
    if(!spaceship.IsAlive()){
        spawnTimer += GetFrameTime();
        if(spawnTimer>=shipSpawnInterval){
            std::cout<<"Ship Respawned";
            spaceship.Respawn();
            spawnTimer =  0.0f;
        }
    }

}

//recalculate difficulty based on remaining aliens
void Game::UpdateDifficulty() {
    int aliveCount = 0;
    for (auto& alien : aliens) {
        if (alien->IsAlive()) aliveCount++;
    }

    int totalAliens = 55; 
    float ratio = (float)aliveCount / totalAliens; 

    // fewer aliens=faster shooting and faster movement
    alienLaserShootInterval = 0.2f + (ratio * 0.5f); 
    alienSpeed = 0.5f + ((1.0f - ratio) * 2.0f);
    // speeds up as they die
}

void Game::DrawScoreUI() {
    DrawText("SCORE", 20, 8, 14, {180, 180, 60, 255});
    DrawText(TextFormat("%05i", score), 20, 22, 22, YELLOW);

    DrawText("LIVES", GetScreenWidth() - 100, 8, 14, {180, 180, 60, 255});
    DrawText(TextFormat("%d", lives), GetScreenWidth() - 100, 22, 22, GREEN);

    DrawLine(0, 45, GetScreenWidth(), 45, {60, 60, 70, 255});
}
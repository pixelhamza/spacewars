#include "game.hpp"
#include<iostream>


Game::Game(){
    obstacles = CreateObstacles(); 
    alienTextures[AlienType::Crab] = LoadTexture("assets/texture/crab.png");
    alienTextures[AlienType::Octopus] = LoadTexture("assets/texture/octopus.png");

    aliens.push_back(std::make_unique<Alien>(Vector2{100,200},AlienType::Crab,alienTextures));


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
    DeleteInactiveBullets();
    std::cout<<"Vector size : "<< spaceship.bullets.size()<<"\n";

}
void Game:: Draw(){ 
    spaceship.Draw();

    for(auto &bullet  : spaceship.bullets){ 
        bullet.Draw();

    }

    for(auto &obstacle : obstacles) obstacle.Draw();

    for(auto &alien : aliens) alien->Draw();
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
}

std::vector<Obstacle> Game::CreateObstacles(){
    int obstacle_width = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (3 * obstacle_width)) / 4;

    for (size_t i{}; i <3 ; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacle_width;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));

    }
    return obstacles;
    
}

   
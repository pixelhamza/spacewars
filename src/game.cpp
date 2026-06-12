#include "game.hpp"
#include<iostream>

Game::Game(){}

Game::~Game(){}


void Game::UpdatePos(){ 
    for(auto &bullet: spaceship.bullets){ 
        bullet.Update();

    }
    DeleteInactiveBullets();
    std::cout<<"Vector size : "<< spaceship.bullets.size()<<"\n";

}
void Game:: Draw(){ 
    spaceship.Draw();

    for(auto bullet  : spaceship.bullets){ 
        bullet.Draw();

    }
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

   
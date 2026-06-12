#pragma once
#include "spaceship.hpp"

class Game{ 
    public: 
        Game(); 
        ~Game();
        void Draw(); 
        void UpdatePos();
        void HandleInput();
        void DeleteInactiveBullets();
    private: 
    Spaceship spaceship;
};
#include "raylib.h"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#include "spaceship.hpp"

int main()
{
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "Spacewars");
    SetTargetFPS(60);
    Spaceship spaceship;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("SPACEWARS", 320, 280, 20, WHITE);
            spaceship.Draw();
            
        EndDrawing();
    }

    CloseWindow();
}
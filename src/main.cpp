#include "raylib.h"
#include "game.hpp"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int main()
{
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "Spacewars");
    SetTargetFPS(60);
    Game game;
    while (!WindowShouldClose())
    {   game.HandleInput();
        game.UpdatePos();
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("SPACEWARS", 320, 280, 20, WHITE);
            game.Draw();
        EndDrawing();
    }

    CloseWindow();
}
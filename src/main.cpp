#include "raylib.h"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int main()
{
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "Spacewars");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("SPACEWARS", 320, 280, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
}
#pragma once
#include "raylib.h"

class Explosion {
    public:
        Explosion(Vector2 position, Texture2D texture, int size = 48, float duration = 0.4f);
        void Update();
        void Draw();
        bool IsFinished() const;

    private:
        Vector2 position;
        Texture2D texture;
        int size;
        float timer = 0.0f;
        float duration;
        static const int frameCount = 8;
        static const int sheetFrameSize = 48;
};
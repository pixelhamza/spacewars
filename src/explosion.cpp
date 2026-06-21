// explosion.cpp
#include "explosion.hpp"
#include <algorithm>
#include<iostream>

Explosion::Explosion(Vector2 position, Texture2D texture, int size, float duration) {
    this->position = position;
    this->texture = texture;
    this->size = size;
    this->duration = duration;
}

void Explosion::Update() {
    timer += GetFrameTime();
}

bool Explosion::IsFinished() const {
    return timer >= duration;
}

void Explosion::Draw() {
    int frame = (int)((timer / duration) * frameCount);
    frame = std::min(frame, frameCount - 1);
    std::cout << "timer: " << timer << " duration: " << duration << " frame: " << frame << "\n";
    Rectangle source = {(float)(frame * sheetFrameSize), 0, (float)sheetFrameSize, (float)sheetFrameSize};
    Rectangle dest = {position.x, position.y, (float)size, (float)size};
    Vector2 origin = {0, 0};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}
#pragma once
#include "raylib.h"
#include <map>

enum class SoundType { Shoot, AlienShoot, Explosion, MysteryShipFly, GameOver };

class AudioManager {
    public:
        AudioManager();
        ~AudioManager();
        void Play(SoundType type);

    private:
        std::map<SoundType, Sound> sounds;
};


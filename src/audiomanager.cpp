#include "audiomanager.hpp"

AudioManager::AudioManager() {
    InitAudioDevice();
    sounds[SoundType::Shoot] = LoadSound("assets/sounds/shoot.wav");
    sounds[SoundType::AlienShoot] = LoadSound("assets/sounds/alien_shoot.wav");
    sounds[SoundType::Explosion]  = LoadSound("assets/sounds/explosion.wav");
    sounds[SoundType::MysteryShipFly] = LoadSound("assets/sounds/mystery.wav");
    sounds[SoundType::GameOver] = LoadSound("assets/sounds/gameover.wav");
    sounds[SoundType::ShipExplode] = LoadSound("assets/sounds/shipexplosion.wav");
}

AudioManager::~AudioManager() {
    for (auto& [type, sound]:sounds) {
        UnloadSound(sound);
    }
    CloseAudioDevice();
}

void AudioManager::Play(SoundType type) {
    if (sounds.count(type)) {
        PlaySound(sounds.at(type));
    }
}
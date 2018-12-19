#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Sound.h>
#include <Game/Object.h>
#include <Game/LevelScene.h>

int Enemy::OnDeath() {
    Scene->AddAnimal(X, Y, false, false, 0, 0, true);
    Scene->AddExplosion(4, false, X, Y);
    Sound::Play(Sound::SFX_DESTROY);
    Active = false;
    return 1;
}

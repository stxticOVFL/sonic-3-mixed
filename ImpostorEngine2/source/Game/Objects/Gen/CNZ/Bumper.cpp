// Object ID: 0x4A
// Object Name: Bumper.cpp

#include "Bumper.h"

typedef IMath Math;

void Bumper::Create() {
    Object::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = Sprite->FindAnimation("Bumper");
}

void Bumper::Update() {
    Object::Update();
}

void Bumper::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    }

int Bumper::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    Player->XSpeed = Player->XSpeed < 0 ? 0x800 : -0x800;
    Player->YSpeed = Player->YSpeed < 0 ? 0x800 : -0x800;
    if (Player->Underwater) {
        Player->XSpeed >>= 1;
        Player->YSpeed >>= 1;
    }

    Player->Ground = false;
    Player->JumpVariable = 0;
    Sound::Play(Sound::SFX_BUMPER);
    return true;
}


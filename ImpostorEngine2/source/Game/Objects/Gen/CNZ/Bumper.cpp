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
    ForceX = 0;
    ForceY = 0;
    ForcePower = 0;
    this->CurrentAnimation = Sprite->FindAnimation("Bumper");
}

void Bumper::Update() {
    Object::Update();
}

void Bumper::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Bumper::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    ForceX = Player->X;
    ForceY = Player->Y;
    ForceX -= X;
    ForceY -= Y;
    ForcePower = Math::atanHex(ForceX, ForceY);
    ForceX = Math::cosHex(ForcePower);
    ForceY = Math::sinHex(ForcePower);
    Player->XSpeed = ForceX >> 5;
    Player->YSpeed = ForceY >> 5;
    if (Player->Underwater) {
        Player->XSpeed >>= 1;
        Player->YSpeed >>= 1;
    }

    Player->Ground = false;
    Player->JumpVariable = 0;
    Sound::Play(Sound::SFX_BUMPER);
    return true;
}


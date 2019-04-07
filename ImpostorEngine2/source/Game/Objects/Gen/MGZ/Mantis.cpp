// Object ID: 0x9D
// Object Name: Mantis.cpp

#include "Mantis.h"

typedef IMath Math;

void Mantis::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 25;
    HitCount = 1;
    wentUp = false;
    Gravity = 0x80;
    StartYpos = this->Y;
    this->Y += 64;
}

int Mantis::OnHit() {
    return OnDeath();
}

void Mantis::Update() {
    CheckDistanceToPlayers();
    if (PlayerXDistance <= 0x200) {
        if (Y == StartYpos) {
            YSpeed = -0xBF0;
        }
        else {
            wentUp = true;
        }
    }

    if (wentUp) YSpeed = 0;

    if (wentUp && Y > StartYpos) {
        YSpeed = 0;
        Y = StartYpos;
    }

    MoveSprite();
    Object::Update();
}

void Mantis::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


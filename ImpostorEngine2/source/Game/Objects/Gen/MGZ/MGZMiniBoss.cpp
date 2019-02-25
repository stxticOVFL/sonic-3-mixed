// Object ID: 0x9F
// Object Name: MGZMiniBoss.cpp

#include "MGZMiniBoss.h"

typedef IMath Math;

void MGZMiniBoss::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 13;
    HitCount = 6;
    this->Y += 1;
}

int MGZMiniBoss::OnHit() {
    HitCount--;
    if (HitCount == 0) {
        Scene->StopTimer = true;
        Scene->Score += 1000;
        HitCount = -1;
        return 0;
    }

    InvulnTimer = 0x20;
    return 0;
}

void MGZMiniBoss::Update() {
    Object::Update();
}

void MGZMiniBoss::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    }

int MGZMiniBoss::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    Player->YSpeed = -Player->YSpeed;
    Player->XSpeed = -Player->XSpeed;
    return true;
}


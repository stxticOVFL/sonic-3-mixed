// Object ID: 0xA1
// Object Name: MGZBoss.cpp

#include "MGZBoss.h"

typedef IMath Math;

void MGZBoss::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 16;
    HitCount = 8;
    this->Y += 1;
}

int MGZBoss::OnHit() {
    Scene->LevelTriggerFlag |= 1 << SubType;
    return OnDeath();
}

void MGZBoss::Update() {
    Object::Update();
}

void MGZBoss::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    }

int MGZBoss::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    Player->YSpeed = -Player->YSpeed;
    Player->XSpeed = -Player->XSpeed;
    return true;
}


// Object ID: 0x9C
// Object Name: Spiker.cpp

#include "Spiker.h"

typedef IMath Math;

void Spiker::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 22;
    HitCount = 1;
    StartYpos = this->Y;
}

int Spiker::OnHit() {
    return 0;
}

void Spiker::Update() {
    CheckDistanceToPlayers();
    if (PlayerXDistance <= 0x80 && Rise == false) {
        Y += 16;
        Rise = true;
    }
    else {
        Y = StartYpos;
    }
    MoveSprite();
    Object::Update();
}

void Spiker::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Spiker::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    if (HitFrom == CollideSide::TOP) {
        Player->YSpeed -= 0x80;
        Player->Action = ActionType::Jumping;
        Sound::Play(Sound::SFX_SPRING);
        return 1;
    }
    else {
        if (Player->Action == ActionType::Jumping) {
            return OnDeath();
        }

    }
    return true;
}


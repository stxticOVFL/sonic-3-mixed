// Object ID: 0x9B
// Object Name: BubblesBadnik.cpp

#include "BubblesBadnik.h"

typedef IMath Math;

void BubblesBadnik::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 20;
    HitCount = 1;
}

int BubblesBadnik::OnHit() {
    return OnDeath();
}

void BubblesBadnik::Update() {
    CheckDistanceToPlayers();
    if (PlayerXDistance <= 0x100) {
        if (sinAngle > 360) {
            reversesin = true;
        }

        if (sinAngle < 0) {
            reversesin = false;
        }

        if (reversesin == false) {
            Y += Math::sinHex(sinAngle++);
            X += Math::sinHex(sinAngle++);
        }

        Y -= Math::sinHex(sinAngle--);
        X -= Math::sinHex(sinAngle--);
    }

    MoveSprite();
    Object::Update();
}

void BubblesBadnik::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


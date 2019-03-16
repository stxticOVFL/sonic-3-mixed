// Object ID: 0xFFFFFFFF
// Object Name: BlastoidShot.cpp

#include "BlastoidShot.h"

typedef IMath Math;

void BlastoidShot::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 8;
    H = 8;
    Invincible = true;
    BounceOffShield = true;
    Timer = 0;
}

void BlastoidShot::Update() {
    Timer = 1 - Timer;
    if (!OnScreen) {
        X = -16;
        Y = -16;
        XSpeed = 0;
        YSpeed = 0;
    }

    Object::Update();
}

void BlastoidShot::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Timer, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


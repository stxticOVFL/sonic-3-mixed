// Object ID: 0xFFFFFFFF
// Object Name: FireBreathBomb.cpp

#include "FireBreathBomb.h"

typedef IMath Math;

void FireBreathBomb::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 10;
    H = 16;
    Frame = 0;
    YSpeed = -0x400;
}

int FireBreathBomb::OnHit() {
    return 0;
}

void FireBreathBomb::Update() {
    SubY += YSpeed * 0x100;
    if (YSpeed < 0 && Y < Scene->CameraY - 24) {
        Active = false;
    }

    Object::Update();
}

void FireBreathBomb::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, 12 + (Scene->Frame >> 1 & 1), X - CamX, Y - CamY, 0, FlipY << 1);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


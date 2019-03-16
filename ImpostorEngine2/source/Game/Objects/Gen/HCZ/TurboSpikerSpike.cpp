// Object ID: 0xFFFFFFFF
// Object Name: TurboSpikerSpike.cpp

#include "TurboSpikerSpike.h"

typedef IMath Math;

void TurboSpikerSpike::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 24;
    H = 42;
    Invincible = true;
    YSpeed = -0x1F0;
    XSpeed = 0x4F * (FlipX ? -1 : 1);
    Timer = 0;
    VisualLayer = 0;
}

void TurboSpikerSpike::Update() {
    Timer = Timer < 4 ? Timer + 1 : 0;
    if (!OnScreen) {
        X = -16;
        Y = -16;
        XSpeed = 0;
        YSpeed = 0;
    }

    Object::Update();
}

void TurboSpikerSpike::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 9, 0, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    G->DrawSprite(Sprite, 10, Timer, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


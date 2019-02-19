// Object ID: 0xFFFFFFFF
// Object Name: BloominatorSpore.cpp

#include "BloominatorSpore.h"

typedef IMath Math;

void BloominatorSpore::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 16;
    H = 16;
    Invincible = true;
    BounceOffShield = true;
}

void BloominatorSpore::Update() {
    Timer += XSpeed;
    Rotation += YSpeed;
    YSpeed += 0x38;
    X = Timer >> 8;
    Y = Rotation >> 8;
    if (!OnScreen) {
        X = -16;
        Y = -16;
        Timer = 0;
        Rotation = 0;
    }

    Object::Update();
}

void BloominatorSpore::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, 4, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }
    }


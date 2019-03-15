// Object ID: 0xFFFFFFFF
// Object Name: BloominatorSpore.cpp

#include "BloominatorSpore.h"

typedef IMath Math;

void BloominatorSpore::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    CleanupInactiveObject = true;
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
    G->DrawSprite(Sprite, CurrentAnimation, 4, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        int32_t spriteWidth = Sprite->Animations[CurrentAnimation].Frames[4].W;
        int32_t spriteHeight = Sprite->Animations[CurrentAnimation].Frames[4].H;
        G->DrawRectangle(X - CamX, Y - CamY, spriteWidth, spriteHeight, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


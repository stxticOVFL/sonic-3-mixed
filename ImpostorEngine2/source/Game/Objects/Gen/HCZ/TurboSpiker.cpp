// Object ID: 0x96
// Object Name: TurboSpiker.cpp

#include "TurboSpiker.h"

typedef IMath Math;

void TurboSpiker::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 16;
    Y += 7;
    CurrentAnimation = 7;
    Flip = 1;
    if (FlipX) Flip = -1;

    HitCount = 1;
}

int TurboSpiker::OnHit() {
    return OnDeath();
}

void TurboSpiker::Update() {
    if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 2) Frame += Sprite->Animations[CurrentAnimation].AnimationSpeed;
    else if (Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration != 0) Frame += 0x100 / Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration;

    if (Frame >= Sprite->Animations[CurrentAnimation].FrameCount << 8) {
        Frame = Sprite->Animations[CurrentAnimation].FrameToLoop << 8;
    }

    Object::Update();
}

void TurboSpiker::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 9, 0, X - CamX, Y - CamY, 0, Flip < 0 ? IE_NOFLIP : IE_FLIPX);
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, Flip < 0 ? IE_NOFLIP : IE_FLIPX);
    }


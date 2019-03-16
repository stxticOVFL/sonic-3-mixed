// Object ID: 0x93
// Object Name: Jawz.cpp

#include "Jawz.h"

typedef IMath Math;

void Jawz::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 48;
    H = 16;
    VisW = 48;
    CurrentAnimation = 15;
    Flip = -2;
    HitCount = 1;
}

int Jawz::OnHit() {
    return OnDeath();
}

void Jawz::Update() {
    if (Flip == -2) {
        if (Scene->Player->EZX > X) Flip = 1;
        else Flip = -1;
    }

    X += Flip * 2;
    if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 2) Frame += Sprite->Animations[CurrentAnimation].AnimationSpeed;
    else if (Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration != 0) Frame += 0x100 / Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration;

    if (Frame >= Sprite->Animations[CurrentAnimation].FrameCount << 8) {
        Frame = Sprite->Animations[CurrentAnimation].FrameToLoop << 8;
    }

    Hurting = false;
    Object::Update();
}

void Jawz::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, Flip < 0 ? IE_NOFLIP : IE_FLIPX);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


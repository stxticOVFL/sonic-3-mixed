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
    Fired = false;
    VisualLayer = -1;
    FireTimer = -1;
    MoveTimer = 0;
    KeptFlip = 0;
}

int TurboSpiker::OnHit() {
    return OnDeath();
}

void TurboSpiker::Update() {
    if (Math::pydistance(X, Y, Scene->Players[0]->X, Scene->Players[0]->Y) <= 0xA0 && VisualLayer == -1) {
        VisualLayer = 1;
        Sound::Play(Sound::SFX_SPLASH);
        FireTimer = 20;
        IApp::Print(0, "%d", SubType);
    }

    FireTimer = FireTimer == 0 ? 0 : FireTimer - 1;
    if (FireTimer == 0 && !Fired && Math::pydistance(X, Y, Scene->Players[0]->X, Scene->Players[0]->Y) <= 0x60) {
        Fired = true;
        KeptFlip = Flip;
        Scene->AddNewObject(Obj_TurboSpikerSpike, 0, X, Y, Flip < 0 ? false : true, false);
        Sound::Play(Sound::SFX_SLIDE);
        XSpeed = 0x250 * Flip;
        YSpeed = 0xFF;
    }

    Flip = (Scene->Players[0]->X >= X && !Fired) ? -1 : (KeptFlip != 0 ? KeptFlip : 1);
    if (!Fired) {
        if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 2) Frame += Sprite->Animations[CurrentAnimation].AnimationSpeed;
        else if (Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration != 0) Frame += 0x100 / Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration;

        if (Frame >= Sprite->Animations[CurrentAnimation].FrameCount << 8) {
            Frame = Sprite->Animations[CurrentAnimation].FrameToLoop << 8;
        }

    }

    if (Fired && !OnScreen) {
        Active = false;
    }
    else {
        MoveTimer = 1 - MoveTimer;
        CurrentAnimation = 6;
    }
    Object::Update();
}

void TurboSpiker::MoveSprite() {
    if (!Fired) return;

    SubX += XSpeed << 8;
    SubY += YSpeed << 8;
    if (YSpeed > 0) {
        if (Scene->CollisionAt(X - (W / 2), Y + (H / 2), this)) {
            SubY -= YSpeed << 8;
        }

    }

}

void TurboSpiker::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        if (20 - FireTimer <= 5) G->DrawSprite(Sprite, 12, 20 - FireTimer, X - CamX, Y - CamY, 0, Flip < 0 ? IE_NOFLIP : IE_FLIPX);

        if (!Fired) G->DrawSprite(Sprite, 9, 0, X - CamX, Y - CamY, 0, Flip < 0 ? IE_NOFLIP : IE_FLIPX);

        G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, Flip < 0 ? IE_NOFLIP : IE_FLIPX);
    }
    }


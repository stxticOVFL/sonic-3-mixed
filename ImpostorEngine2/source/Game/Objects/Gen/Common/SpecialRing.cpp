// Object ID: 0x85
// Object Name: SpecialRing.cpp

#include "SpecialRing.h"

typedef IMath Math;

void SpecialRing::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 8;
    H = 64;
    VisW = 64;
    VisH = 64;
    HyperColor = 0xFFFF00;
    HyperRing = true;
    percent = 0;
    HyperRing = Scene->ZoneID >= 7;
    GoTimer = -1;
    StoredX = 0;
    StoredY = 0;
}

void SpecialRing::Update() {
    if (this->HyperRing) {
        Timer = Scene->Frame << 5 & 0x7FF;
        if (Timer < 0x200) {
            percent = (Timer - 0x000) & 0x1FF;
            if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

            HyperColor = G->ColorBlendHex(0xF2D141, 0x6181F2, percent);
        }
        else if (Timer < 0x400) {
            percent = (Timer - 0x200) & 0x1FF;
            if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

            HyperColor = G->ColorBlendHex(0xF2D141, 0x41C241, percent);
        }
        else if (Timer < 0x600) {
            percent = (Timer - 0x400) & 0x1FF;
            if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

            HyperColor = G->ColorBlendHex(0xF2D141, 0xF28141, percent);
        }
        else if (Timer < 0x800) {
            percent = (Timer - 0x600) & 0x1FF;
            if (percent >= 0x100) percent = (percent & 0xFF) ^ 0xFF;

            HyperColor = G->ColorBlendHex(0xF2D141, 0x8141F2, percent);
        }

    }

    if (GoTimer > 0) {
        Scene->Player->EZX = StoredX;
        Scene->Player->EZY = StoredY;
        GoTimer--;
    }

    if (GoTimer == 0) {
        Scene->FadeAction = 7;
        Scene->FadeTimerMax = 24 + 24;
        Scene->FadeMax = 0x104;
        G->FadeToWhite = true;
        Sound::Play(Sound::SFX_SS_WARP);
        GoTimer = -1;
        Active = false;
    }

    if (GoTimer > 0) {
        Sprite = Scene->Objects3Sprite;
        int LoopPoint = Sprite->Animations[CurrentAnimation].FrameToLoop;
        int FrameCount = Sprite->Animations[CurrentAnimation].FrameCount;
        if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 0 && Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration != 0) Frame += ((0x100 * Sprite->Animations[CurrentAnimation].AnimationSpeed * 0x100) >> 8) / Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration;

        if (Frame >= FrameCount * 0x100) {
            Frame = FrameCount * 0x100 - 0x100;
        }

    }

    Object::Update();
}

void SpecialRing::Render(int CamX, int CamY) {
    if (GoTimer >= 0) {
        G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, (Frame >> 8) < 8);
        return;
    }

    G->DrawModelOn2D(Scene->GiantRingModel, this->X - CamX, this->Y - CamY, 1.0, 0, Scene->Frame & 0xFF, (Scene->Frame / 5) & 0xFF, HyperColor, false);
    }

int SpecialRing::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (PlayerID != 0) return 0;

    if (GoTimer >= 0) return 0;

    if (Scene->Player->HyperForm) {
        Scene->Player->GiveRing(50);
        Active = false;
    }
    else if (Scene->Player->SuperForm || true) {
        Scene->Player->GiveRing(50);
        Active = false;
    }
    else {
        Scene->Player->GiveRing(50);
        Scene->Player->Hidden = true;
        GoTimer = 48;
        StoredX = Scene->Player->EZX;
        StoredY = Scene->Player->EZY;
        App->Audio->FadeMusic(1.0);
        Frame = 0;
        CurrentAnimation = 0;
    }
    Sound::Play(Sound::SFX_ENTER_SS_RING);
    return 1;
}

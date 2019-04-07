// Object ID: 0x39
// Object Name: LargeFan.cpp

#include "LargeFan.h"

typedef IMath Math;

void LargeFan::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 48;
    H = 64;
    CurrentAnimation = 12;
    OutY = 0;
    PlayingSound = false;
}

void LargeFan::Update() {
    bool Out = false;
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (Scene->Players[i]->X > X) {
            Out = true;
        }

    }
    if (OnScreen && !PlayingSound) {
        Sound::Loop(Sound::SFX_FAN_BIG, 43923);
        PlayingSound = true;
    }

    if (Sprite->Animations.size() > CurrentAnimation) {
        if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 2) Frame += Sprite->Animations[CurrentAnimation].AnimationSpeed;
        else if (Sprite->Animations[CurrentAnimation].Frames[Frame / 0x100].Duration != 0) Frame += 0x100 / Sprite->Animations[CurrentAnimation].Frames[Frame / 0x100].Duration;

        if (Frame / 0x100 >= Sprite->Animations[CurrentAnimation].FrameCount - 1) {
            Frame = Sprite->Animations[CurrentAnimation].FrameToLoop * 0x100;
        }

    }

    if (Out) {
        OutY += (66 - OutY) / 4;
    }
    else {
        OutY += (-2 - OutY) / 4;
    }
    Object::Update();
}

int LargeFan::OnLeaveScreen() {
    Sound::Stop(Sound::SFX_FAN_BIG);
    PlayingSound = false;
    return 0;
}

void LargeFan::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY + OutY, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


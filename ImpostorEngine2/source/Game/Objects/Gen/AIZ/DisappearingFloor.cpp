// Object ID: 0x29
// Object Name: DisappearingFloor.cpp

#include "DisappearingFloor.h"

typedef IMath Math;

CONSTRUCTER DisappearingFloor::DisappearingFloor() {
    BinIndex = LevelScene::LoadSpriteBin("AIZ/Disappearing Floor.bin");
}

void DisappearingFloor::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    DoDeform = true;
    SolidTop = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Rotation = 0;
    W = 64;
    H = 48;
    Offset = SubType >> 4;
    Period = SubType & 0xF;
    PeriodFrames = (2 << Period) - 1;
    Period -= 3;
    if (Period < 0) Period = 0;

    Offset <<= Period;
    Visible = true;
    CurrentAnimation = Sprite->FindAnimation("Disappearing Floor");
    Frame = 4;
}

void DisappearingFloor::Update() {
    bool SolidoNaso = false;
    int tiem = (Scene->Frame + Offset) & PeriodFrames;
    if (tiem < 64) {
        SolidoNaso = false;
        if (tiem >= 48) {
            tiem = 63 - tiem;
            SolidoNaso = true;
        }

        if (tiem < 16) {
            if (tiem == 0) {
                Frame = 4;
                if (OnScreen) Sound::Play(Sound::SFX_SPLASH);

            }
            else if (tiem < 4) {
                Frame = 3;
            }
            else if (tiem < 7) {
                Frame = 2;
                SolidTop = SolidoNaso;
            }
            else if (tiem < 9) {
                Frame = 1;
            }
            else if (tiem < 12) {
                Frame = 0;
            }
            else {
                Frame = -1;
            }
            Frame++;
        }

    }

    Object::Update();
}

void DisappearingFloor::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (Frame >= 4) {
        G->DrawSprite(Sprite, CurrentAnimation + 1, (Scene->Frame >> 2) & 3, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


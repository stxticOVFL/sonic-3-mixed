// Object ID: 0x82
// Object Name: CutsceneKnuckles.cpp

#include "CutsceneKnuckles.h"

typedef IMath Math;

void CutsceneKnuckles::Create() {
    Object::Create();
    W = 32;
    H = 32;
    Active = true;
    Priority = true;
    CurrentAnimation = 0;
    Frame = 0;
    Sprite = Scene->KnuxSprite[0];
    CustomFrameToLoop = -1;
    CustomFrameToCount = -1;
    X += 128;
    SubX = X << 16;
    SubY = Y << 16;
    Timer = -1;
    RoutineNumber = 0;
    Ground = false;
}

void CutsceneKnuckles::HCZ2() {
    int offX = App->WIDTH / 2 - 0xA0;
    int TimerMax = 60 * 3 + 64 + 32 + 64;
    if (Scene->CameraX >= 0x3910 - offX && RoutineNumber != -1) {
        if (RoutineNumber < 1) {
            Scene->CameraMinX = Scene->CameraX;
            Scene->CameraMaxX = 0x3940 - offX;
        }

        FlipX = true;
        if (Scene->Player->Ground && Timer == -1) {
            Timer = TimerMax;
            App->Audio->FadeMusic(1.5);
        }

        if (Timer == TimerMax - 88) {
            App->Audio->PushMusicAt(Sound::SoundBank[0xF2], 4.328, true, 0);
        }

        if (Timer == TimerMax - 90 - 64) {
            CurrentAnimation = 5;
            Frame = 0;
            XSpeed = -0x200;
        }

        if (Timer > TimerMax - 90 - 64 - 32 - 64) {
            if ((SubX >> 16) <= InitialX + 32) {
                CurrentAnimation = 0;
                Frame = 0;
                XSpeed = 0;
            }

        }

        if (Timer == TimerMax - 90 - 64 - 32 - 64) {
            XSpeed = -0x100;
            YSpeed = -0x400;
            Ground = false;
            Frame = 0;
            RoutineNumber = 1;
            CurrentAnimation = 10;
        }

        if (RoutineNumber == 1 && Ground) {
            XSpeed = 0x100;
            YSpeed = -0x400;
            Ground = false;
            Frame = 0;
            RoutineNumber = 2;
            CurrentAnimation = 10;
            Scene->LevelTriggerFlag = 0x80;
            Scene->CameraMaxX = 0xFFFF;
            App->Audio->FadeMusic(1.5);
        }

        if (RoutineNumber == 2 && Ground) {
            XSpeed = 0;
            YSpeed = 0;
            Frame = 54 << 8;
            CurrentAnimation = 1;
            CustomFrameToLoop = 55;
            CustomFrameToCount = 67;
            RoutineNumber = -1;
        }

        if (Timer > 0) {
            Timer--;
        }

    }

}

void CutsceneKnuckles::Update() {
    if (Scene->ZoneID == 2 && Scene->Act == 2) HCZ2();

    if (!Ground) YSpeed += 0x38;

    if (Ground) {
        while (Scene->CollisionAt(SubX >> 16, (SubY >> 16) + 20 - 1)) {
            SubY -= 1 << 16;
        }

    }
    else {
        while (Scene->CollisionAt(SubX >> 16, (SubY >> 16) + 20 - 1) && YSpeed > 0) {
            SubY -= 1 << 16;
            Ground = true;
            YSpeed = 0;
        }

    }
    SubX += XSpeed << 8;
    SubY += YSpeed << 8;
    X = SubX >> 16;
    Y = SubY >> 16;
    int LoopPoint = Sprite->Animations[CurrentAnimation].FrameToLoop;
    int FrameCount = Sprite->Animations[CurrentAnimation].FrameCount;
    if (CustomFrameToLoop >= 0) LoopPoint = CustomFrameToLoop;

    if (CustomFrameToCount > 0) FrameCount = CustomFrameToCount;

    if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 0 && Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration != 0) Frame += ((0x100 * Sprite->Animations[CurrentAnimation].AnimationSpeed * 0x100) >> 8) / Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].Duration;

    if (Frame >= FrameCount * 0x100) {
        Frame = LoopPoint * 0x100;
    }

    Object::Update();
}

void CutsceneKnuckles::Render(int CamX, int CamY) {
    if (Scene->ZoneID == 2 && Scene->Act == 2) G->DrawSprite(Scene->SpriteMap["HCZ"], 0, 0, InitialX - 4 - CamX, InitialY + 20 - CamY, 0, IE_NOFLIP);

    G->DrawSprite(Scene->KnuxSprite[0], CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, !FlipX ? IE_NOFLIP : IE_FLIPX);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

void CutsceneKnuckles::Chuckle() {
    Frame = 54 << 8;
    CustomFrameToLoop = 54;
    CurrentAnimation = 1;
}


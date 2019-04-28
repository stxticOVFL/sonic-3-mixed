// Object ID: 0xFFFFFFFF
// Object Name: AIZIntroKnux.cpp

#include "AIZIntroKnux.h"

typedef IMath Math;

void AIZIntroKnux::Create() {
    Object::Create();
    Priority = true;
    Sprite = LevelScene::LoadSpriteFromBin("Players/AIZCutscene.bin", SaveGame::CurrentMode);
    JumpAnim = Sprite->FindAnimation("KJump");
    CurrentAnimation = JumpAnim + 1;
    Frame = 0;
    Action = 1;
    ActionTimer = 10;
    AnimTimer = 0;
    Gravity = 0x38;
    Floor = InitialY + 0xF;
    FlipX = true;
    StayGrounded = false;
    PebbleX = X + 0x20;
    PebbleY = InitialY;
    EmeraldsX = X - 0x10;
    EmeraldsY = InitialY;
    DisplayEmeralds = true;
    Y += 0x35;
    AllowGrounded = false;
    LandStarted = false;
    LandFinished = false;
}

void AIZIntroKnux::Update() {
    if (StayGrounded || (Y >= Floor && AllowGrounded)) {
        YSpeed = 0;
        Y = Floor;
    }

    if (StayGrounded) Gravity = 0;

    if (Action == 1) {
        CurrentAnimation = JumpAnim + 1;
        if (ActionTimer >= 5) {
            YSpeed = -0x600;
        }
        else AllowGrounded = true;
        ActionTimer--;
        if (Y == Floor) {
            Action = 2;
            FlipX = true;
        }

        if (ActionTimer >= 0) EmeraldsX += ActionTimer * 2;

        Cutscene_KnucklesBackForth = 8;
    }

    if (Cutscene_KnucklesBackForth > 0 && Action == 2) {
        if (!LandStarted) {
            Frame = 0;
            LandStarted = true;
            FlipX = true;
        }

        CurrentAnimation = JumpAnim + 2;
        if (CurrentAnimation == JumpAnim + 2 && (Frame + 1) == 4) LandFinished = true;

        if (LandFinished) {
            CurrentAnimation = JumpAnim + 3;
            FlipX = false;
        }

        StayGrounded = true;
        Cutscene_KnucklesBackForth--;
    }

    if (Cutscene_KnucklesBackForth <= 0 && Action == 2) {
        FlipX = false;
        CurrentAnimation = JumpAnim + 3;
        Action = 3;
        ActionTimer = 40;
    }

    if (Action == 3) {
        ActionTimer--;
        FlipX = false;
        if (ActionTimer <= 0) {
            Action = 4;
        }

    }

    if (Action == 4) {
        CurrentAnimation = JumpAnim + 4;
        if (ActionTimer < 32 && Cutscene_KnucklesBackForth == 0) {
            ActionTimer++;
            if (ActionTimer >= 31) {
                Cutscene_KnucklesBackForth++;
            }

        }
        else {
            ActionTimer--;
            X += 10;
            if (X >= EmeraldsX + 0xF) DisplayEmeralds = false;

            CurrentAnimation = JumpAnim;
        }
        if (ActionTimer <= 0) {
        }

    }

    AnimTimer++;
    if (AnimTimer > Sprite->Animations[CurrentAnimation].Frames[Frame].Duration / Sprite->Animations[CurrentAnimation].AnimationSpeed) {
        Frame++;
        if (Frame >= Sprite->Animations[CurrentAnimation].FrameCount) {
            Frame = Sprite->Animations[CurrentAnimation].FrameToLoop;
        }

        AnimTimer = 0;
    }

    Object::Update();
}

void AIZIntroKnux::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, JumpAnim + 5, 0, PebbleX - CamX, PebbleY - CamY, 0, IE_NOFLIP);
    if (DisplayEmeralds) G->DrawSprite(Sprite, JumpAnim + 6, 0, EmeraldsX - CamX, EmeraldsY - CamY, 0, IE_NOFLIP);

    if (CurrentAnimation == -1) return;

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }

void AIZIntroKnux::UpdateSubType() {
    if (SubType == 1) {
        Action = 1;
        ActionTimer = 30;
    }
    else {
        Action = 2;
    }
}


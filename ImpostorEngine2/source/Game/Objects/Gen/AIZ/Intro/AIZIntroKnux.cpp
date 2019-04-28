// Object ID: 0xFFFFFFFF
// Object Name: AIZIntroKnux.cpp

#include "AIZIntroKnux.h"

typedef IMath Math;

void AIZIntroKnux::Create() {
    Object::Create();
    Priority = true;
    Sprite = LevelScene::LoadSpriteFromBin("Players/AIZCutscene.bin", SaveGame::CurrentMode);
    JumpAnim = Sprite->FindAnimation("KJump");
    CurrentAnimation = -1;
    Frame = 0;
    Action = 1;
    ActionTimer = 120;
    AnimTimer = 0;
    Gravity = 0x38;
    Floor = Y + 0x9;
    FlipX = true;
    StayGrounded = false;
    PebbleX = X + 0x20;
    PebbleY = Y;
}

void AIZIntroKnux::Update() {
    if (SubY >= Floor || StayGrounded) {
        YSpeed = 0;
        Y = Floor;
    }
    else YSpeed += Gravity;
    if (Action == 1) {
        CurrentAnimation = JumpAnim + 1;
        if (ActionTimer >= 90) YSpeed = -0x600;

        ActionTimer--;
        Cutscene_KnucklesBackForth = 10;
    }

    if (Cutscene_KnucklesBackForth > 0 && Action == 2) {
        CurrentAnimation = JumpAnim + 2;
        StayGrounded = true;
        Cutscene_KnucklesBackForth--;
    }

    if (Cutscene_KnucklesBackForth <= 0 && Action == 2) {
        CurrentAnimation = JumpAnim + 3;
        Action = 3;
        ActionTimer = 20;
    }

    if (Action == 3) {
        ActionTimer--;
        if (ActionTimer <= 0) {
            Action = 4;
        }

    }

    if (Action == 4) {
        FlipX = false;
        CurrentAnimation = JumpAnim + 4;
        if (ActionTimer < 16 && Cutscene_KnucklesBackForth == 0) {
            ActionTimer++;
            if (ActionTimer == 15) {
                Cutscene_KnucklesBackForth++;
            }

        }
        else {
            ActionTimer--;
            X += 10;
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
    if (CurrentAnimation == -1) return;

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }

void AIZIntroKnux::UpdateSubType() {
    if (SubType == 1) {
        Action = 1;
        ActionTimer = 30;
    }
    else {
        Cutscene_KnucklesBackForth = SubType;
        Action = 2;
    }
}


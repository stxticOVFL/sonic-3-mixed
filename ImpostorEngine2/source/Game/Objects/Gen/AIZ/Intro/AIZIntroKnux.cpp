// Object ID: 0xFFFFFFFF
// Object Name: AIZIntroKnux.cpp

#include "AIZIntroKnux.h"

typedef IMath Math;

void AIZIntroKnux::Create() {
    Object::Create();
    Priority = true;
    Sprite = LevelScene::LoadSpriteFromBin("Players/AIZCutscene.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("KJump");
    Frame = 0;
    Action = 0;
    ActionTimer = 0;
    GRV = 0;
}

void AIZIntroKnux::Update() {
    YSpeed += GRV;
    if (Scene->RoutineNumber == 2) {
        YSpeed = -0x400;
        GRV = 0x38;
    }

    Object::Update();
}

void AIZIntroKnux::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }


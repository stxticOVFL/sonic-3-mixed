// Object ID: 0xFFFFFFFF
// Object Name: AIZIntroKnux.cpp

#include "AIZIntroKnux.h"

typedef IMath Math;

void AIZIntroKnux::Create() {
    Object::Create();
    Priority = true;
    Sprite = LevelScene::LoadSpriteFromBin("Players/Knux.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Jump");
    Frame = 0;
    Action = 0;
    ActionTimer = 0;
    Gravity = 0.21875;
}

void AIZIntroKnux::Update() {
    if (Scene->RoutineNumber == 2) {
    }

    Object::Update();
}

void AIZIntroKnux::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }


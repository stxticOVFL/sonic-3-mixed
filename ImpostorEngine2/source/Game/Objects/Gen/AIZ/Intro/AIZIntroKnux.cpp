// Object ID: 0xFFFFFFFF
// Object Name: AIZIntroKnux.cpp

#include "AIZIntroKnux.h"

typedef IMath Math;

void AIZIntroKnux::Create() {
    Object::Create();
    Priority = true;
    Sprite = LevelScene::LoadSpriteFromBin("Player/Knux.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Jump");
    Frame = 0;
}

void AIZIntroKnux::Update() {
    Object::Update();
}

void AIZIntroKnux::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, Animation, Frame, X - CamX, Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }


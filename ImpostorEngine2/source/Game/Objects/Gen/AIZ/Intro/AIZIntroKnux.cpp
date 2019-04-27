// Object ID: 0xFFFFFFFF
// Object Name: AIZIntroKnux.cpp

#include "AIZIntroKnux.h"

typedef IMath Math;

void AIZIntroKnux::Create() {
    Object::Create();
    Priority = true;
    Sprite = LevelScene::LoadSpriteFromBin("Dev/NullGfx.bin", SaveGame::CurrentMode);
    Frame = 0;
    Action = 0;
    ActionTimer = 0;
}

void AIZIntroKnux::Update() {
    if (Action == 1) {
        Y -= 2;
        ActionTimer--;
        if (ActionTimer < 0) {
            Action = 0;
        }

    }

    if (Cutscene_KnucklesBackForth > 0 && Action == 2) {
        if (Cutscene_KnucklesBackForth >= 30) X -= 8;
        else X += 8;
        if (Cutscene_KnucklesBackForth % 10 == 0) Y += 2;

        Cutscene_KnucklesBackForth--;
        ActionTimer = 24;
    }

    if (Cutscene_KnucklesBackForth <= 0 && Action == 2) {
        Y += 2;
        ActionTimer--;
        if (ActionTimer < 0) {
            Action = 3;
            ActionTimer = 20;
        }

    }

    if (Action == 3) {
        ActionTimer--;
        if (ActionTimer <= 0) {
            Action = 4;
        }

    }

    if (Action == 4) {
        if (ActionTimer < 16 && Cutscene_KnucklesBackForth == 0) {
            ActionTimer++;
            if (ActionTimer == 15) {
                Cutscene_KnucklesBackForth++;
            }

        }
        else {
            ActionTimer--;
            X += 8;
        }
        if (ActionTimer <= 0) {
        }

    }

    Object::Update();
}

void AIZIntroKnux::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
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


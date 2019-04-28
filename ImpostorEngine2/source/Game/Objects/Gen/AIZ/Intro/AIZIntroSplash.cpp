// Object ID: 0xFFFFFFFF
// Object Name: AIZIntroSplash.cpp

#include "AIZIntroSplash.h"

typedef IMath Math;

void AIZIntroSplash::Create() {
    Object::Create();
    Priority = true;
    Sprite = LevelScene::LoadSpriteFromBin("AIZ/Intro.bin", SaveGame::CurrentMode);
    if (Sprite) {
        Sprite->SetTransparentColorIndex(0);
        CurrentAnimation = Sprite->FindAnimation("Waves");
    }

    FrameTimer = 0;
}

void AIZIntroSplash::Update() {
    FrameTimer++;
    if (FrameTimer >= 4) {
        Frame++;
        if (Frame > 5) {
            Visible = false;
        }

    }

    X -= 16;
    Object::Update();
}

void AIZIntroSplash::Render(int CamX, int CamY) {
    if (!Visible || !Active) return;

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X, Y - 32, 0, IE_NOFLIP);
    }


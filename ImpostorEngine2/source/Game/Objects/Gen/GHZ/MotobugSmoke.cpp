// Object ID: 0xFFFFFFFF
// Object Name: MotobugSmoke.cpp

#include "MotobugSmoke.h"

typedef IMath Math;

CONSTRUCTER MotobugSmoke::MotobugSmoke() {
    BinIndex = LevelScene::LoadSpriteBin("Sprites/GHZ/Motobug.bin");
    SmokeTime = 8;
}

void MotobugSmoke::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    CleanupInactiveObject = true;
    AutoAnimate = false;
    W = 16;
    H = 16;
    VisW = 16;
    VisH = 16;
    Frame = 0;
    Acceleration = 150;
    CurrentAnimation = 0;
}

void MotobugSmoke::Update() {
    MoveWithParent();
    X += FlipX ? -0x18 : 0x18;
    if (SmokeTime == 0) {
        Frame = 0;
        Active = false;
    }
    else {
        SmokeTime--;
        Frame++;
    }
    Object::Update();
}

void MotobugSmoke::Render(int CamX, int CamY) {
    if (CurrentAnimation == -1) {
        return;
    }

    if (Frame < 0) {
        return;
    }

    if (!Visible) {
        return;
    }

    G->DrawSprite(Sprite, 3, Frame, X - CamX, Y - CamY, Rotation, FlipX | FlipY << 1);
    }


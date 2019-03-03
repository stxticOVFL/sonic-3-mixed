// Object ID: 0xFFFFFFFF
// Object Name: Motobug.cpp

#include "Motobug.h"

typedef IMath Math;

CONSTRUCTER Motobug::Motobug() {
    BinIndex = LevelScene::LoadSpriteBin("Sprites/GHZ/Motobug.bin");
}

void Motobug::Create() {
    Object::Create();
    Active = true;
    W = 39;
    H = 28;
}

void Motobug::Update() {
    Object::Update();
}

void Motobug::Render(int CamX, int CamY) {
    if (CurrentAnimation == -1) {
        return;
    }

    if (Frame < 0) {
        return;
    }

    if (!Visible) {
        return;
    }

    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, Rotation, FlipX | FlipY << 1);
    }
    }


// Object ID: 0xFFFFFFFF
// Object Name: Motobug.cpp

#include "Motobug.h"

typedef IMath Math;

CONSTRUCTER Motobug::Motobug() {
    BinIndex = LevelScene::LoadSpriteBin("Sprites/GHZ/Motobug.bin");
}

void Motobug::Create() {
    Object::Create();
    W = 16;
    H = 16;
}

void Motobug::Update() {
    Object::Update();
}

void Motobug::Render(int CamX, int CamY) {
    }


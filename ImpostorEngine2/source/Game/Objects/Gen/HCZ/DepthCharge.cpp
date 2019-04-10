// Object ID: 0xFFFFFFFF
// Object Name: DepthCharge.cpp

#include "DepthCharge.h"

typedef IMath Math;

CONSTRUCTER DepthCharge::DepthCharge() {
}

void DepthCharge::Create() {
    Object::Create();
    W = 16;
    H = 16;
    BinIndex = LevelScene::LoadSpriteBin("HCZ/BigShaker.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Depth Charge");
}


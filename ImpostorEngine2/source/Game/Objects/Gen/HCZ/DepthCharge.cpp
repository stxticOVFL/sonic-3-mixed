// Object ID: 0xFFFFFFFF
// Object Name: DepthCharge.cpp

#include "DepthCharge.h"

typedef IMath Math;

void DepthCharge::Create() {
    Object::Create();
    W = 16;
    H = 16;
    Sprite = LevelScene::LoadSpriteFromBin("HCZ/BigShaker.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Depth Charge");
}


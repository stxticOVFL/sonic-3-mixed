// Object ID: 0xB8
// Object Name: HarmfulIce.cpp

#include "HarmfulIce.h"

typedef IMath Math;

CONSTRUCTER HarmfulIce::HarmfulIce() {
    BinIndex = LevelScene::LoadSpriteBin("ICZ/Harmful Ice.bin");
}

void HarmfulIce::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    Invincible = true;
    CurrentAnimation = Sprite->FindAnimation("Harmful Ice");
    W = 32;
    if (SubType == 0) {
        H = 48;
        Frame = 1;
    }
    else {
        H = 32;
        Frame = 0;
    }
}

void HarmfulIce::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }


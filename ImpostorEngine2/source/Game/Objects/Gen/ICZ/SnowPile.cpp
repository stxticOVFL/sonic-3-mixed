// Object ID: 0xB9
// Object Name: SnowPile.cpp

#include "SnowPile.h"

typedef IMath Math;

CONSTRUCTER SnowPile::SnowPile() {
    BinIndex = LevelScene::LoadSpriteBin("ICZ/Snowpile.bin");
}

void SnowPile::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    VisualLayer = -1;
    H = 16;
    W = 64;
    CurrentAnimation = Sprite->FindAnimation("SnowPile");
}

void SnowPile::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int SnowPile::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    Scene->Players[PlayerID]->XSpeed /= 2;
    return 1;
}


// Object ID: 0x47
// Object Name: CNZRotatingBarrel.cpp

#include "CNZRotatingBarrel.h"

typedef IMath Math;

CONSTRUCTER CNZRotatingBarrel::CNZRotatingBarrel() {
    BinIndex = LevelScene::LoadSpriteBin("CNZ/Cylinder.bin");
}

void CNZRotatingBarrel::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Timer = 1;
    Frame = 0;
    W = 32;
    H = 32;
    CurrentAnimation = Sprite->FindAnimation("Cylinder");
}

void CNZRotatingBarrel::Update() {
    Object::Update();
}

void CNZRotatingBarrel::Render(int CamX, int CamY) {
    Timer -= 1;
    if (Timer < 0) {
        Timer = 1;
        Frame += 1;
        Frame = Frame & 3;
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int CNZRotatingBarrel::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    return true;
}


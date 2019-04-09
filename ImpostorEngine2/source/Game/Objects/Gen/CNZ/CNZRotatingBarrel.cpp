// Object ID: 0x47
// Object Name: CNZRotatingBarrel.cpp

#include "CNZRotatingBarrel.h"

typedef IMath Math;

CONSTRUCTER CNZRotatingBarrel::CNZRotatingBarrel() {
    BinIndex = LevelScene::LoadSpriteBin("CNZ/Cylinder.bin");
}

void CNZRotatingBarrel::Create() {
    Object::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = Sprite->FindAnimation("Cylinder");
}

void CNZRotatingBarrel::Update() {
    Object::Update();
}

void CNZRotatingBarrel::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 4, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
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

}


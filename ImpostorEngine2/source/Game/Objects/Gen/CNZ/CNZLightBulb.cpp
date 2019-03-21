// Object ID: 0x45
// Object Name: CNZLightBulb.cpp

#include "CNZLightBulb.h"

typedef IMath Math;

void CNZLightBulb::Create() {
    Object::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = Sprite->FindAnimation("Light Bulb");
}

void CNZLightBulb::Update() {
    if (Y > Scene->WaterLevel) {
        Broken = true;
    }

    Object::Update();
}

void CNZLightBulb::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


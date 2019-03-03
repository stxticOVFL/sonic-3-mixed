// Object ID: 0x45
// Object Name: LightBulb.cpp

#include "LightBulb.h"

typedef IMath Math;

void LightBulb::Create() {
    Object::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = Sprite->FindAnimation("Light Bulb");
}

void LightBulb::Update() {
    if (Y > Scene->WaterLevel) {
        Broken = true;
    }

    Object::Update();
}

void LightBulb::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    }


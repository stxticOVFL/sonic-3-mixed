// Object ID: 0x52
// Object Name: MGZSmashingPillar.cpp

#include "MGZSmashingPillar.h"

typedef IMath Math;

void MGZSmashingPillar::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 80;
    CurrentAnimation = 10;
    X += 0x10;
}

void MGZSmashingPillar::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    }


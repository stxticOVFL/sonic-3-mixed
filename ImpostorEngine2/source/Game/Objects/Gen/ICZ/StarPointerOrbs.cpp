// Object ID: 0xFFFFFFFF
// Object Name: StarPointerOrbs.cpp

#include "StarPointerOrbs.h"

typedef IMath Math;

void StarPointerOrbs::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    Frame = 1;
    W = 32;
    H = 32;
}

void StarPointerOrbs::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }


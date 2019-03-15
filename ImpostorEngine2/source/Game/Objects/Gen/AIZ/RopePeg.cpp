// Object ID: 0x0A
// Object Name: RopePeg.cpp

#include "RopePeg.h"

typedef IMath Math;

void RopePeg::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    CurrentAnimation = 1;
    W = 80;
    H = 80;
}

void RopePeg::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


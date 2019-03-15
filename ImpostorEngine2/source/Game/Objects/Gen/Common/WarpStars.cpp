// Object ID: 0xFFFFFFFF
// Object Name: WarpStars.cpp

#include "WarpStars.h"

typedef IMath Math;

void WarpStars::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = false;
    W = 16;
    H = 16;
    Rotation = 0;
    Activated = true;
    this->Frame = 0;
    CleanupInactiveObject = true;
}

void WarpStars::Update() {
    Object::Update();
}

void WarpStars::Render(int CamX, int CamY) {
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int WarpStars::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Activated) {
    }

    return 1;
}


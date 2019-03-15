// Object ID: 0xFFFFFFFF
// Object Name: StarPointerOrbs.cpp

#include "StarPointerOrbs.h"

typedef IMath Math;

void StarPointerOrbs::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Frame = 1;
    W = 32;
    H = 32;
}

void StarPointerOrbs::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0x80);
    }

    G->DrawSprite(Sprite, CurrentAnimation, 6, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int StarPointerOrbs::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Scene->Players[PlayerID]) return 0;

    if (Scene->Players[PlayerID]->Shield == ShieldType::None) Scene->Players[PlayerID]->Hurt(Scene->Players[PlayerID]->X, false);
    else Active = false;
    return 1;
}


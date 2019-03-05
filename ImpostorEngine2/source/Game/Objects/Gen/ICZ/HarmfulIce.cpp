// Object ID: 0xB8
// Object Name: HarmfulIce.cpp

#include "HarmfulIce.h"

typedef IMath Math;

void HarmfulIce::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    CurrentAnimation = Sprite->FindAnimation("Harmful Ice");
    W = 32;
    if (SubType == 0) {
        H = 48;
        Frame = 1;
    }
    else {
        H = 32;
        Frame = 0;
    }
}

void HarmfulIce::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int HarmfulIce::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Scene->Players[PlayerID]->Action != ActionType::Hurt) {
        Scene->Players[PlayerID]->Hurt(X, true);
    }

    return 1;
}


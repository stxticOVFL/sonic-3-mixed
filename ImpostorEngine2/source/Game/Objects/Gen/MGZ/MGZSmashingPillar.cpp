// Object ID: 0x52
// Object Name: MGZSmashingPillar.cpp

#include "MGZSmashingPillar.h"

typedef IMath Math;

void MGZSmashingPillar::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    DoDeform = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 62;
    H = 80;
    CurrentAnimation = 9;
    OGY = Y - 5 + 5;
    YSpeed = -0x50;
    Direction = true;
    VisualLayer = 1;
}

void MGZSmashingPillar::Update() {
    if (Direction) {
        if (Y == OGY - 20) {
            YSpeed = 0;
            while (Timer < 200) {
                Timer++;
            }

            Timer = 0;
            YSpeed = 0x250;
            Direction = false;
        }

    }
    else {
        if (Y == OGY + 80) {
            YSpeed = 0;
            while (Timer < 2000) {
                Timer++;
            }

            Timer = 0;
            YSpeed = -0x50;
            Direction = true;
        }

    }
    Object::Update();
}

void MGZSmashingPillar::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int MGZSmashingPillar::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (HitFrom == CollideSide::BOTTOM && Scene->Players[PlayerID]->YSpeed <= 0) {
        Scene->Players[PlayerID]->Hurt(X, true);
    }

    return 1;
}


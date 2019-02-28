// Object ID: 0x5B
// Object Name: TopPlatform.cpp

#include "TopPlatform.h"

typedef IMath Math;

void TopPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    CurrentAnimation = 11;
    W = 48;
    H = 24;
    InUse = false;
    Gravity = 0x50;
    PlayerUsed = -1;
}

void TopPlatform::Update() {
    if (PlayerUsed == -1) return;

    Scene->Players[PlayerUsed]->X = X;
    Scene->Players[PlayerUsed]->Y = Y - 24;
    Scene->Players[PlayerUsed]->Ground = true;
    YSpeed = (Math::abs(Scene->Players[PlayerUsed]->XSpeed) / 5) * -1;
    XSpeed = Scene->Players[PlayerUsed]->XSpeed / 7 + (XFriction / 2);
    XFriction = XSpeed;
    if (Math::abs(XSpeed) < 0x200) {
        if (XSpeed > 0) {
            XSpeed = 0x200;
        }
        else {
            XSpeed = -0x200;
        }
    }

    Object::Update();
}

void TopPlatform::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int TopPlatform::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (HitFrom == CollideSide::TOP && !InUse) {
        InUse = true;
        PlayerUsed = PlayerID;
        Y -= 24;
    }

    return 1;
}


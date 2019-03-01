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
    AlreadyUsed = false;
    Gravity = 0x50;
    PlayerUsed = -1;
}

void TopPlatform::Update() {
    if (AlreadyUsed) {
        XSpeed = XSpeed / 7 + (XFriction / 1.1);
        XFriction = XSpeed;
        YSpeed += 0xA0;
    }

    if (PlayerUsed == -1) return;

    IPlayer* Player = Scene->Players[PlayerUsed];
    if (Player->Action == ActionType::Hurt || Player->InputJump) {
        Gravity = 0;
        PlayerUsed = -1;
        InUse = false;
        AlreadyUsed = true;
        return;
    }

    Player->SubX = SubX;
    Player->SubY = (Y - 32) << 16;
    Player->Ground = true;
    YSpeed = (Math::abs(Player->XSpeed) / 3) * -1;
    if (Math::abs(XSpeed / 7 + (XFriction / 1.1)) > 0x250) {
        XSpeed = XSpeed > 0 ? 0x250 : -0x250;
        XFriction /= 1.1;
    }
    else {
        XSpeed = Player->XSpeed / 7 + (XFriction / 1.1);
        XFriction = XSpeed;
    }
    if (Player->Action == ActionType::CrouchDown) {
        Gravity = 0xE0;
    }
    else if (Player->Action == ActionType::LookUp) {
        Gravity = -0x40;
    }
    else {
        Gravity = 0x50;
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
        Y -= 2;
    }

    return 1;
}


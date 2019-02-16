// Object ID: 0xFFFFFFFF
// Object Name: Platform.cpp

#include "Platform.h"

typedef IMath Math;

void Platform::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 64;
    int i = 0;
    Type = Attributes[0];
    AmplitudeX = Attributes[1];
    Speed = Attributes[2];
    HasTension = Attributes[3];
    FrameID = Attributes[4];
    Collision = Attributes[5];
    TileOriginX = Attributes[6];
    ChildCount = Attributes[7];
    Angle = Attributes[8];
    if (Collision == 0) SolidTop = true;
    else Solid = true;
    switch (FrameID) {
        case 0:
        W = 32;
        H = 32;
        break;
        case 1:
        W = 64;
        H = 64;
        break;
        case 3:
        W = 64;
        H = 64;
        break;
        case 4:
        W = 64;
        H = 64;
        break;
        case 2:
        W = 64;
        H = 16;
        break;
        case 5:
        W = 160;
        H = 48;
        break;
        case 6:
        W = 248;
        H = 96;
        break;
    }

}

void Platform::Update() {
    Object::Update();
}

void Platform::Render(int CamX, int CamY) {
    G->DrawRectangle(X - CamX - W / 2, Y - CamY - H / 2, W, H, 0xFFFFFF);
    }

int Platform::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (PlayerID != 0) return 0;

    if (Type != PlatformType::PUSHABLE) return 0;

    if (((Scene->Players[PlayerID]->WallLeft && Scene->Players[PlayerID]->InputLeft) || (Scene->Players[PlayerID]->Action == ActionType::Spindash && Scene->Players[PlayerID]->DisplayFlip < 0)) && HitFrom == CollideSide::RIGHT) {
        if (X <= InitialX - Speed * 16) return 0;

        X = SubX >> 16;
        SubX -= 0x1000;
        Scene->Players[PlayerID]->X = X + W / 2 + Scene->Players[PlayerID]->W / 2 - 2;
    }

    if (((Scene->Players[PlayerID]->WallRight && Scene->Players[PlayerID]->InputRight) || (Scene->Players[PlayerID]->Action == ActionType::Spindash && Scene->Players[PlayerID]->DisplayFlip > 0)) && HitFrom == CollideSide::LEFT) {
        if (X >= InitialX + Speed * 16) return 0;

        X = SubX >> 16;
        SubX += 0x1000;
        Scene->Players[PlayerID]->X = X - W / 2 - Scene->Players[PlayerID]->W / 2 + 2;
    }

    return 1;
}


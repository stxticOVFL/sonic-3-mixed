// Object ID: 0x2E
// Object Name: SpikedLog.cpp

#include "SpikedLog.h"

typedef IMath Math;

void SpikedLog::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 64;
    H = 16;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    CurrentAnimation = 31;
    Direction = 0;
    Period = 0;
    Spin = 0;
    WaterCount = Scene->WaterEnteredCounter;
}

void SpikedLog::Update() {
    Direction = -1;
    if (BeingStoodOn) {
        Direction = 1;
    }

    if (WaterCount != Scene->WaterEnteredCounter) {
        if (Period < 0x80) {
            Direction = 1;
        }
        else {
            WaterCount = Scene->WaterEnteredCounter;
        }
    }

    Period += Direction * 8;
    if (BeingStoodOn) {
        if (Period > 0x80) {
            Period = 0x80;
        }

    }

    if (Period < 0) {
        Period = 0;
        Direction = 0;
    }

    if (Period > 0xFF) {
        Period = 0;
        Direction = 0;
    }

    Spin = (Spin - Direction * 4) & 0xFF;
    if (Period == 0) {
        if (Spin > 0) Spin -= 4;

    }

    Y = InitialY - 3 + (Math::cosHex(Period + 0x80) >> 14) + 4;
    Frame = ((Spin + 0x180) & 0xFF) >> 4;
    Object::Update();
}

void SpikedLog::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int SpikedLog::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Frame >= 13 || Frame < 3) {
        if (Scene->Players[PlayerID]->YSpeed >= 0 && Scene->Players[PlayerID]->EZY < Y && Scene->Players[PlayerID]->Ground) {
            Scene->Players[PlayerID]->Hurt(X, true);
        }

    }
    else if (Scene->Players[PlayerID]->YSpeed <= 0 && Scene->Players[PlayerID]->EZY > Y) {
        Scene->Players[PlayerID]->Hurt(X, true);
    }

    return 0;
}


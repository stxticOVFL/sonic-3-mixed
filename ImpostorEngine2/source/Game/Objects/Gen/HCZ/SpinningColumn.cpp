// Object ID: 0x68
// Object Name: SpinningColumn.cpp

#include "SpinningColumn.h"

typedef IMath Math;

void SpinningColumn::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    SolidTop = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 32;
    H = 64;
    Timer = 0;
    YS = -1;
    if (FlipX) YS = 1;

    LastX = X;
    LastY = Y;
    MoveType = SubType & 0x03;
    ColumnType = SubType & 0xF0;
    MotionDirection = 1;
    if ((SubType & 0xF) == 2) {
        YS <<= 1;
    }

    if (ColumnType == 0xE0) MotionDirection = -1;

    CurrentAnimation = 15;
}

void SpinningColumn::Update() {
    int d0;
    int d1;
    LastX = X;
    LastY = Y;
    if (MoveType == 0) {
    }
    else if (MoveType == 1) {
        d1 = MotionDirection;
        if (d1 < 0) {
            d0 = ColumnType + d1;
            if (d0 == 0) MotionDirection = -MotionDirection;

        }
        else {
            d0 = ColumnType + d1;
            if (d0 == 0xE0) MotionDirection = -MotionDirection;

        }
        ColumnType = d0;
        d0 -= 0x70;
        if (FlipX) d0 = -d0;

        d0 += InitialX;
        X = d0;
        XSpeed = (X - LastX) << 8;
    }
    else if (MoveType == 2) {
        Y = InitialY + 32 * Math::abs(YS) - ((Math::cosHex(Scene->Frame) * 32 * YS) >> 16);
    }

    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (Scene->Players[i]->Action == ActionType::Dead) continue;

        if (Scene->Players[i]->Ground && Scene->Players[i]->EZY > Y - 64 && Scene->Players[i]->EZY < Y - 32 && Scene->Players[i]->EZX > X - 16 && Scene->Players[i]->EZX < X + 16 && Scene->Players[i]->ObjectControlled == 0x7E) {
            Scene->Players[i]->EZY = Y - 32 - Scene->Players[i]->H / 2;
            Scene->Players[i]->DisplayFlip = -1;
            Scene->Players[i]->Action = ActionType::Spinning;
        }

    }
    
	AutoAnimate = true;
    Object::Update();
}

void SpinningColumn::Render(int CamX, int CamY) {
    int nX = LastX;
    int nY = Y;
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, nX - CamX, nY - CamY, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int SpinningColumn::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Scene->Players[PlayerID]->EZY + Scene->Players[PlayerID]->H / 2 > Y - 32 && Scene->Players[PlayerID]->EZY - Scene->Players[PlayerID]->H / 2 < Y + 32 && Scene->Players[PlayerID]->EZX + Scene->Players[PlayerID]->W / 2 > X - 16 && Scene->Players[PlayerID]->EZX - Scene->Players[PlayerID]->W / 2 < X + 16) {
        if (Scene->Players[PlayerID]->EZX < X) {
            Scene->Players[PlayerID]->EZX -= (Scene->Players[PlayerID]->EZX + Scene->Players[PlayerID]->W / 2) - (X - 16);
            Scene->Players[PlayerID]->GroundSpeed = 0;
            Scene->Players[PlayerID]->XSpeed = 0;
        }
        else {
            Scene->Players[PlayerID]->EZX += (X + 16) - (Scene->Players[PlayerID]->EZX - Scene->Players[PlayerID]->W / 2);
            Scene->Players[PlayerID]->GroundSpeed = 0;
            Scene->Players[PlayerID]->XSpeed = 0;
        }
    }

    if (Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->EZY > Y - 64 && Scene->Players[PlayerID]->EZY < Y - 32 && Scene->Players[PlayerID]->EZX > X - 16 && Scene->Players[PlayerID]->EZX < X + 16) {
        Scene->Players[PlayerID]->ObjectControlled = 0x7E;
        Scene->Players[PlayerID]->EZX = X;
        Scene->Players[PlayerID]->GroundSpeed = 0;
        Scene->Players[PlayerID]->Action = ActionType::Spinning;
        return 1;
    }

    return 0;
}


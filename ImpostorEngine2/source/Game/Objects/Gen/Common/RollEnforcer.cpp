// Object ID: 0x26
// Object Name: RollEnforcer.cpp

#include "RollEnforcer.h"

typedef IMath Math;

void RollEnforcer::Create() {
    Object::Create();
    Active = true;
    W = 28;
    H = 28;
}

void RollEnforcer::Update() {
    Object::Update();
}

void RollEnforcer::Render(int CamX, int CamY) {
    if (!Scene->maxLayer) {
        G->DrawSprite(Scene->EditorSprite, 1, 6, X - CamX, Y - CamY, 0, 0);
    }

    }

int RollEnforcer::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* player = Scene->Players[PlayerID];
    if (!player->Ground) return 0;

    if (player->GroundSpeed == 0) {
        if ((SubType & 0xF) != 0x4) {
            if ((player->DisplayFlip < 0) == this->FlipX) {
                player->SubX &= 0xFFFF0000;
                player->SubY &= 0xFFFF0000;
                player->ForceRoll = true;
                player->GroundSpeed = Math::sign(player->DisplayFlip) * 0x580;
                player->Ground = true;
            }
            else {
                player->ForceRoll = false;
            }
        }

    }
    else {
        if ((SubType & 0xF) != 0x4) {
            if ((player->GroundSpeed < 0) == this->FlipX) {
                player->SubX &= 0xFFFF0000;
                player->SubY &= 0xFFFF0000;
                player->ForceRoll = true;
                player->GroundSpeed = Math::sign(player->XSpeed) * 0x580;
                player->Ground = true;
            }
            else {
                player->ForceRoll = false;
            }
        }
        else {
            player->SubX &= 0xFFFF0000;
            player->SubY &= 0xFFFF0000;
            player->ForceRoll = false;
        }
    }
    return 1;
}


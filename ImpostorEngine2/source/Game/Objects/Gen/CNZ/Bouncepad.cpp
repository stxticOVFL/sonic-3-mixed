// Object ID: 0x4B
// Object Name: Bouncepad.cpp

#include "Bouncepad.h"

typedef IMath Math;

void Bouncepad::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    W = (SubType & 0xF0) << 1;
    H = 16;
}

int Bouncepad::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return 0;
    }

    if (Player->DisplayFlip == 1) {
        Player->XSpeed = 0x800;
    }
    else {
        Player->XSpeed = -0x800;
    }
    Player->Ground = false;
    Player->YSpeed = (FlipY & 1) ? 0x800 : -0x800;
    Player->GroundSpeed = Player->XSpeed;
    Player->InputAlarm = 0x0f;
    if (Player->Action == ActionType::Rolling) {
        Player->Action = ActionType::Normal;
    }

    if (Player->Angle == 0) {
        Player->Action = ActionType::Normal;
        if (Player->DisplayFlip == 1) {
            Player->Angle = 1;
        }
        else {
            Player->Angle = -1;
        }
        Player->SpringFlip = 3;
    }

    Sound::Play(Sound::SFX_PAD_BOUNCE);
    return 1;
}


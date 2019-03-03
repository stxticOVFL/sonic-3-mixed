// Object ID: 0x0E
// Object Name: Ridge.cpp

#include "Ridge.h"

typedef IMath Math;

void Ridge::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
}

int Ridge::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Scene->Players[PlayerID]->Action == ActionType::Dead) return 0;

    if (!FlipX) {
        if (Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->GroundSpeed >= 0x400 && Scene->Players[PlayerID]->EZX >= X - 0x10 && Scene->Players[PlayerID]->EZX <= X + 0x10 && Scene->Players[PlayerID]->EZY >= Y - 0x14 && Scene->Players[PlayerID]->EZY <= Y + 0x20 && Scene->Players[PlayerID]->DisplayFlip == 1) {
            Scene->Players[PlayerID]->SpringFlip = 4;
            Scene->Players[PlayerID]->Action = ActionType::Spring;
            Scene->Players[PlayerID]->XSpeed += 0x400;
            Scene->Players[PlayerID]->YSpeed = -0x700;
            Scene->Players[PlayerID]->Ground = false;
        }

    }
    else {
        if (Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->GroundSpeed <= -0x400 && Scene->Players[PlayerID]->EZX >= X - 0x10 && Scene->Players[PlayerID]->EZX <= X + 0x10 && Scene->Players[PlayerID]->EZY >= Y - 0x14 && Scene->Players[PlayerID]->EZY <= Y + 0x20 && Scene->Players[PlayerID]->DisplayFlip == 1) {
            Scene->Players[PlayerID]->Action = ActionType::Spring;
            Scene->Players[PlayerID]->XSpeed -= 0x400;
            Scene->Players[PlayerID]->YSpeed = -0x700;
            Scene->Players[PlayerID]->Ground = false;
        }

    }
    return 1;
}


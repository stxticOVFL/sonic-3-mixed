// Object ID: 0x6B
// Object Name: InvisibleDeath.cpp

#include "InvisibleDeath.h"

typedef IMath Math;

void InvisibleDeath::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Painful = false;
    Deadly = true;
    if (!Deadly) Solid = true;

    Scene->AddSelfToRegistry(this, "Solid");
    Rotation = 0;
    Size = 1 + (SubType & 0xF0) / 0x10;
    W = (SubType & 0xF0) + 0x10;
    H = ((SubType & 0x0F) << 4) + 0x10;
    if (Deadly) {
    }

}

int InvisibleDeath::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Scene->Players[PlayerID]->Action == ActionType::Dead) return 0;

    if (Painful) {
        if (HitFrom == CollideSide::TOP && Rotation == 0 && Scene->Players[PlayerID]->YSpeed >= 0) {
            Scene->Players[PlayerID]->Hurt(X, true);
        }
        else if (HitFrom == CollideSide::BOTTOM && Rotation == 180 && Scene->Players[PlayerID]->YSpeed <= 0) {
            Scene->Players[PlayerID]->Hurt(X, true);
        }
        else if ((Rotation == 90 && HitFrom == CollideSide::LEFT) || (Rotation == 270 && HitFrom == CollideSide::RIGHT)) {
            if (Scene->Players[PlayerID]->Y + 20 - 4 - 4 <= Y - 16) return 0;

            Scene->Players[PlayerID]->Hurt(X, true);
        }

    }
    else if (Deadly) {
        Scene->Players[PlayerID]->Die(false);
    }

    return 1;
}


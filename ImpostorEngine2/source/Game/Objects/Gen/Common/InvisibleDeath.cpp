// Object ID: 0x6B
// Object Name: InvisibleDeath.cpp

#include "InvisibleDeath.h"

typedef IMath Math;

void InvisibleDeath::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    CleanupInactiveObject = true;
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

void InvisibleDeath::UpdateSubType() {
    Size = 1 + (SubType & 0xF0) / 0x10;
    W = (SubType & 0xF0) + 0x10;
    H = ((SubType & 0x0F) << 4) + 0x10;
    if (Deadly) {
    }

}

uint8_t InvisibleDeath::GetSubTypeIncrement() {
    return 1;
}

uint8_t InvisibleDeath::GetSubTypeMax() {
    return 99;
}

void InvisibleDeath::Render(int CamX, int CamY) {
    if (!Scene->maxLayer) {
        int32_t x0 = ((X + 32 / -2) + 8) - CamX;
        int32_t y0 = ((Y + 32 / -2) + 8) - CamY;
        int32_t x1 = ((X + 32 / 2) - 8) - CamX;
        int32_t y1 = ((Y + 32 / 2) - 8) - CamY;
        G->DrawSprite(Scene->ItemsSprite, 2, 12, x0, y0, 0, 0);
        G->DrawSprite(Scene->ItemsSprite, 2, 12, x0, y1, 0, 0);
        G->DrawSprite(Scene->ItemsSprite, 2, 12, x1, y0, 0, 0);
        G->DrawSprite(Scene->ItemsSprite, 2, 12, x1, y1, 0, 0);
        if (isHeldDebugObject) {
            G->DrawRectangle(X - CamX - 16, Y - 16 - CamY, W, H, 0);
        }

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


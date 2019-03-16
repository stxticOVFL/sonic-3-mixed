// Object ID: 0x59
// Object Name: MGZDashTrigger.cpp

#include "MGZDashTrigger.h"

typedef IMath Math;

void MGZDashTrigger::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    Rev = 0;
    SolidCustomized = true;
    Scene->AddSelfToRegistry(this, "Solid");
}

void MGZDashTrigger::Update() {
    if (Rev & 1) {
        Frame = (Frame + 1) & 3;
    }

    if (Rev > 0) Rev--;

    Object::Update();
}

void MGZDashTrigger::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 1, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    if (Rev & 1) G->DrawSprite(Sprite, 1, 4, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);

    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int MGZDashTrigger::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    int i;
    if ((Scene->Players[PlayerID]->Action == ActionType::Spindash) || (Scene->Players[PlayerID]->DropDashRev >= 71)) {
        Scene->LevelTriggerFlag |= 1 << (SubType & 0xF);
        Rev = 60;
    }

    if (Scene->Players[PlayerID]->EZY < Y - 8 && Rev > 0 && Scene->Players[PlayerID]->Ground) {
        Scene->Players[PlayerID]->Action = ActionType::Jumping;
        Scene->Players[PlayerID]->JumpVariable = 0;
        Scene->Players[PlayerID]->Ground = false;
        if (FlipX) {
            i = Math::atanHex(Scene->Players[PlayerID]->EZX - (X + 16), Scene->Players[PlayerID]->EZY - (Y + 16));
        }
        else {
            i = Math::atanHex(Scene->Players[PlayerID]->EZX - (X - 16), Scene->Players[PlayerID]->EZY - (Y + 16));
        }
        Scene->Players[PlayerID]->XSpeed = (0x680 * Math::cosHex(i)) >> 16;
        Scene->Players[PlayerID]->YSpeed = (0x680 * Math::sinHex(i)) >> 16;
    }

    return true;
}

int MGZDashTrigger::CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough) {
    if (Scene->Players[PlayerID]->EZY < Y - 8) {
        if (FlipX) {
            if ((probeX - (X + 16)) * (probeX - (X + 16)) + (probeY - (Y + 16)) * (probeY - (Y + 16)) < 32 * 32) {
                return 1;
            }

        }
        else if (!FlipX) {
            if ((probeX - (X - 16)) * (probeX - (X - 16)) + (probeY - (Y + 16)) * (probeY - (Y + 16)) < 32 * 32) {
                return 1;
            }

        }

    }

    if (Scene->Players[PlayerID]->EZY >= Y - 8) {
        if (probeX >= X - 16 && probeY >= Y - 16 && probeX < X + 16 && probeY < Y + 16) {
            return 1;
        }

    }

    return 0;
}


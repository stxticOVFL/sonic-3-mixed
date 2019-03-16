// Object ID: 0x3E
// Object Name: HCZConveyorBelt.cpp

#include "HCZConveyorBelt.h"

typedef IMath Math;

void HCZConveyorBelt::Create() {
    Object::Create();
    StartX = 0xB28;
    EndX = 0xCD8;
    Active = true;
    Priority = true;
    W = 16;
    H = 16;
}

void HCZConveyorBelt::Update() {
    switch (SubType & 0xF) {
        case 1:
        StartX = 0xBA8;
        EndX = 0xCD8;
        break;
        case 2:
        StartX = 0xBA8;
        EndX = 0xCD8;
        break;
        case 3:
        StartX = 0xEA8;
        EndX = 0x1058;
        break;
        case 4:
        StartX = 0x11A8;
        EndX = 0x12D8;
        break;
        case 5:
        StartX = 0x1928;
        EndX = 0x19D8;
        break;
        case 6:
        StartX = 0x21A8;
        EndX = 0x2358;
        break;
        case 7:
        StartX = 0x21A8;
        EndX = 0x2358;
        break;
        case 8:
        StartX = 0x22A8;
        EndX = 0x2458;
        break;
        case 9:
        StartX = 0x23A8;
        EndX = 0x2558;
        break;
        case 10:
        StartX = 0x2528;
        EndX = 0x26D8;
        break;
        case 11:
        StartX = 0x26A8;
        EndX = 0x27D8;
        break;
        case 12:
        StartX = 0x26A8;
        EndX = 0x2958;
        break;
        case 13:
        StartX = 0x2728;
        EndX = 0x28D8;
        break;
        case 14:
        StartX = 0x3328;
        EndX = 0x3458;
        break;
        case 15:
        StartX = 0x3328;
        EndX = 0x33D8;
        break;
    }

    for (int p = 0; p < Scene->PlayerCount; p++)
{
        if (Scene->Players[p]->Action == ActionType::Hurt || Scene->Players[p]->Action == ActionType::Dead) continue;

        if (Scene->Players[p]->ObjectControlled == 0 && Scene->Players[p]->JumpVariable == 1 && Scene->Players[p]->GrabTimer == 0 && Scene->Players[p]->EZX >= StartX && Scene->Players[p]->EZX <= EndX && Y >= Scene->Players[p]->EZY - 0x4 && Y < Scene->Players[p]->EZY + 0xC) {
            Scene->Players[p]->ObjectControlled = 4;
            Scene->Players[p]->Action = ActionType::Conveyor;
            Scene->Players[p]->Data2 = SubType;
        }

        if (Scene->Players[p]->ObjectControlled == 4 && Scene->Players[p]->Data2 == SubType) {
            Scene->Players[p]->EZY = Y;
            Scene->Players[p]->XSpeed = 0;
            Scene->Players[p]->YSpeed = 0;
            if (FlipX) Scene->Players[p]->XSpeed = -0x200;
            else Scene->Players[p]->XSpeed = 0x200;
            if (Scene->Players[p]->InputLeft) Scene->Players[p]->XSpeed -= 0x100;

            if (Scene->Players[p]->InputRight) Scene->Players[p]->XSpeed += 0x100;

            if (Scene->Players[p]->InputJump) {
                Scene->Players[p]->ObjectControlled = 0;
                Scene->Players[p]->Jump();
                Scene->Players[p]->YSpeed = -0x500;
                Scene->Players[p]->GrabTimer = 50 - ((SubType >> 4) << 5);
                Scene->Players[p]->Data2 = 0;
            }

            if (Scene->Players[p]->EZX < StartX || Scene->Players[p]->EZX > EndX) {
                Scene->Players[p]->ObjectControlled = 0;
                Scene->Players[p]->Ground = false;
                Scene->Players[p]->Angle = 0;
                Scene->Players[p]->AngleMode = 0;
                Scene->Players[p]->ShieldUsable = false;
                Scene->Players[p]->JumpVariable = 1;
                Scene->Players[p]->Action = ActionType::Jumping;
                Scene->Players[p]->YSpeed = 0;
                Scene->Players[p]->GrabTimer = 16;
                Scene->Players[p]->Data2 = 0;
                Scene->Players[p]->EZX -= Scene->Players[p]->XSpeed >> 8;
                Scene->Players[p]->XSpeed = 0;
            }

        }

    }
    Object::Update();
}

void HCZConveyorBelt::Render(int CamX, int CamY) {
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


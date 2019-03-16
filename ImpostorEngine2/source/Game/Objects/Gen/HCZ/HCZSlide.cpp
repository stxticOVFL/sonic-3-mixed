// Object ID: 0x69
// Object Name: HCZSlide.cpp

#include "HCZSlide.h"

typedef IMath Math;

void HCZSlide::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 60;
    H = 60;
    for (int i = 0; i < 8; i++)
{
        PlayersGot[i] = 0;
    }
    Bottom = false;
    if ((SubType & 0xF0) == 0x80) {
        Bottom = true;
    }

    SlideType = 0;
    switch (SubType & 0xF) {
        case 1:
        SlideType = 1;
        break;
        case 2:
        SlideType = 1;
        break;
        case 3:
        SlideType = 0;
        break;
        case 4:
        SlideType = 2;
        break;
        case 5:
        SlideType = 3;
        break;
        case 6:
        SlideType = 0;
        break;
        case 7:
        SlideType = 1;
        break;
    }

}

int HCZSlide::GetX(int TheY) {
    int finalX = X;
    if (!Bottom) {
        switch (SlideType) {
            case 0:
            finalX += 0x40;
            break;
            case 1:
            finalX += 0x180;
            break;
            case 2:
            case 3:
            finalX += 0x140;
            break;
        }

    }

    if (Bottom || true) {
        int calcX = 0;
        int calcY = 0;
        int slidePieces[10];
        switch (SlideType) {
            case 0:
            slidePieces[0] = 3;
            slidePieces[1] = 0;
            slidePieces[2] = 1;
            slidePieces[3] = 1;
            break;
            case 1:
            slidePieces[0] = 8;
            slidePieces[1] = 0;
            slidePieces[2] = 0;
            slidePieces[3] = 1;
            slidePieces[4] = 0;
            slidePieces[5] = 0;
            slidePieces[6] = 0;
            slidePieces[7] = 0;
            slidePieces[8] = 1;
            slidePieces[9] = 9;
            break;
            case 2:
            slidePieces[0] = 7;
            slidePieces[1] = 0;
            slidePieces[2] = 1;
            slidePieces[3] = 0;
            slidePieces[4] = 0;
            slidePieces[5] = 0;
            slidePieces[6] = 0;
            slidePieces[7] = 1;
            break;
            case 3:
            slidePieces[0] = 9;
            slidePieces[1] = 0;
            slidePieces[2] = 1;
            slidePieces[3] = 1;
            slidePieces[4] = 1;
            slidePieces[5] = 0;
            slidePieces[6] = 0;
            slidePieces[7] = 0;
            slidePieces[8] = 0;
            slidePieces[9] = 1;
            break;
        }

        for (int i = 1; i < 1 + slidePieces[0]; i++)
{
            if (slidePieces[i] == 0) {
                if (TheY >= calcY && TheY < calcY + 0x60) {
                    calcX += (TheY - calcY) * -2 / 3;
                    break;
                }

                calcX -= 0x40;
                calcY += 0x60;
            }
            else if (slidePieces[i] == 1) {
                if (TheY >= calcY && TheY < calcY + 384) {
                    calcX += (40 * Math::sinHex((TheY - calcY) * 128 / 192)) >> 16;
                    break;
                }

                calcY += 384;
            }

        }
        finalX += calcX;
    }

    return finalX;
}

int HCZSlide::GetWidth() {
    switch (SlideType) {
        case 0:
        return 64;
        break;
        case 1:
        return 384;
        break;
        case 2:
        case 3:
        return 320;
        break;
    }

    return 0;
}

int HCZSlide::GetHeight() {
    switch (SlideType) {
        case 0:
        return 96 + 384 + 384;
        break;
        case 1:
        return 96 + 96 + 384 + 96 + 96 + 96 + 96 + 384;
        break;
        case 2:
        return 96 + 384 + 96 + 96 + 96 + 96 + 384;
        break;
        case 3:
        return 96 + 384 + 384 + 384 + 96 + 96 + 96 + 96 + 384;
        break;
    }

    return 0;
}

void HCZSlide::Update() {
    int progress = -1;
    int MyHeight;
    for (int p = 0; p < 8; p++)
{
        if (PlayersGot[p]) {
            if (Scene->Players[p]->GroundSensorHeightMin < 0) {
                Scene->Players[p]->GroundSensorHeightMin = Scene->Players[p]->EZY;
            }

            progress = -1;
            if (SubType >= 0x80) {
                Scene->Players[p]->GroundSensorHeightMin -= Scene->Players[p]->GroundSensorHeight >> 8;
                Scene->Players[p]->GroundSensorHeight -= Math::sign(Scene->Players[p]->GroundSensorHeight) * 0xC;
                progress = Y - Scene->Players[p]->GroundSensorHeightMin;
            }
            else {
                Scene->Players[p]->GroundSensorHeightMin += Scene->Players[p]->GroundSensorHeight >> 8;
                Scene->Players[p]->GroundSensorHeight += Math::sign(Scene->Players[p]->GroundSensorHeight) * 0xC;
                progress = Y + GetHeight() - 0xC0 - Scene->Players[p]->GroundSensorHeightMin;
            }
            Scene->Players[p]->EZX = GetX(progress);
            Scene->Players[p]->EZY = Scene->Players[p]->GroundSensorHeightMin - 4;
            Scene->Players[p]->Ground = true;
            Scene->Players[p]->Action = ActionType::Rolling;
            Scene->Players[p]->GroundSpeed = Scene->Players[p]->GroundSensorHeight;
            Scene->Players[p]->Angle = 64;
            MyHeight = GetHeight() - 0x118 + 0x28;
            if ((progress >= MyHeight || (Scene->Players[p]->GroundSensorHeight >> 8) < 1) && SubType >= 0x80) {
                PlayersGot[p] = 0;
                Scene->Players[p]->EZX += 8;
                Scene->Players[p]->ObjectControlled = 0;
                Scene->Players[p]->Ground = true;
                Scene->Players[p]->Angle = 0x40;
                Scene->Players[p]->AngleMode = 3;
                Scene->Players[p]->GroundSpeed = -Scene->Players[p]->GroundSensorHeight;
                if ((Scene->Players[p]->GroundSensorHeight >> 8) < 1) {
                    Scene->Players[p]->Ground = false;
                    Scene->Players[p]->XSpeed = 0;
                    Scene->Players[p]->YSpeed = 0;
                    Scene->Players[p]->Angle = 0x0;
                    Scene->Players[p]->AngleMode = 0;
                }

            }

            if (progress <= (Scene->Players[p]->GroundSensorHeight >> 8) && SubType < 0x80) {
                PlayersGot[p] = 0;
                Scene->Players[p]->ObjectControlled = 0;
                Scene->Players[p]->Ground = true;
                Scene->Players[p]->Angle = 0x20;
                Scene->Players[p]->AngleMode = 0;
                Scene->Players[p]->GroundSpeed = Scene->Players[p]->GroundSensorHeight;
            }

        }

    }
    Object::Update();
}

void HCZSlide::Render(int CamX, int CamY) {
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX - W / 2, Y - CamY - H / 2, W, H, SubType >= 0x80 ? 0xFF0000 : 0x0000FF);
        G->SetDrawAlpha(0xFF);
    }

    }

int HCZSlide::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if ((SubType & 0xF0) == 0x00 && Scene->Players[PlayerID]->GroundSpeed < 0 && Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->EZX > X + 2) {
        Scene->Players[PlayerID]->Layer = 0;
    }

    if ((SubType & 0xF0) == 0x80 && Scene->Players[PlayerID]->GroundSpeed > 0 && Scene->Players[PlayerID]->Ground) {
        Scene->Players[PlayerID]->Layer = 0;
    }

    if (PlayersGot[PlayerID] == 0 && Scene->Players[PlayerID]->Ground) {
        if ((((SubType & 0xF0) == 0x80) && Scene->Players[PlayerID]->GroundSpeed < 0 && Scene->Players[PlayerID]->EZX < X - 2) || (((SubType & 0xF0) == 0x00) && Scene->Players[PlayerID]->GroundSpeed > 0 && Scene->Players[PlayerID]->EZY > Y + 16)) {
            PlayersGot[PlayerID] = 1;
            Scene->Players[PlayerID]->GroundSensorHeight = Math::abs(Scene->Players[PlayerID]->GroundSpeed);
            Scene->Players[PlayerID]->GroundSensorHeightMin = -1;
            Scene->Players[PlayerID]->ObjectControlled = 0x80;
            Scene->Players[PlayerID]->Action = ActionType::Rolling;
            Priority = true;
        }

    }

    return true;
}


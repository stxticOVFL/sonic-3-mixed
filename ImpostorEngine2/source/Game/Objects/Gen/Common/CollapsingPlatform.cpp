// Object ID: 0x04
// Object Name: CollapsingPlatform.cpp

#include "CollapsingPlatform.h"

typedef IMath Math;

void CollapsingPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 48;
    H = 32;
    f = -1;
    Allotted = 60 * 5;
    Separation = 2;
    Sections = 8;
    Vsect = 2;
    CurrentAnimation = -1;
    SolidTop = true;
    SolidCustomized = true;
    Scene->AddSelfToRegistry(this, "Solid");
    if (Scene->ZoneID == 1) {
        W = 0x30;
        H = 0x20;
        if (Scene->Act == 2) H = 0x18;

        CurrentAnimation = 6;
        if (Scene->Act == 2) CurrentAnimation = 7;

        Frame = 0;
    }
    else if (Scene->ZoneID == 2) {
    }
    else if (Scene->ZoneID == 3) {
    }
    else if (Scene->ZoneID == 5) {
        W = 0x30;
        H = 0x2C;
        CurrentAnimation = 0;
    }
    else if (Scene->ZoneID == 6) {
    }

    VisW = W;
    VisH = H * 2 + 16;
    W <<= 1;
    H <<= 1;
}

void CollapsingPlatform::Update() {
    SolidTop = true;
    if (f > -1 && f <= Allotted) {
        SolidTop = false;
        Solid = false;
        if (f == Allotted) Break();

    }

    if (f > 0) f -= 1;

    Object::Update();
}

void CollapsingPlatform::Break() {
    Sound::Play(Sound::SFX_COLLAPSE);
    if (!Sprite) return;

    int x = X - W / 2 + 8;
    int y = Y - H / 2 + 8;
    int w = W >> 4;
    int h = H >> 4;
    int left = Sprite->Animations[CurrentAnimation].Frames[Frame].X;
    int top = Sprite->Animations[CurrentAnimation].Frames[Frame].Y;
    switch (Scene->ZoneID) {
        case 1:
        {
            if (Scene->Act == 2) {
                x = X - W / 2 + 8;
                y = Y - 0x40 / 2 + 8;
                w = W >> 4;
                h = 0x40 >> 4;
            }

            break;
        }
        case 5:
        {
            y -= 4;
            break;
        }
    }

    bool side = FlipX;
    if (side) {
        for (int i = 0; i < w; i++)
{
            for (int j = 0; j < h; j++)
{
                Scene->AddMovingSprite(Sprite, x + i * 0x10, y + j * 0x10, left + (w - 1 - i) * 0x10, top + j * 0x10, 0x10, 0x10, -8, -8, side, false, 0, 0, 0x70, (h - 1 - j) * 2 + i * h * 2);
            }
        }
    }
    else {
        for (int i = 0; i < w; i++)
{
            for (int j = 0; j < h; j++)
{
                Scene->AddMovingSprite(Sprite, x + i * 0x10, y + j * 0x10, left + i * 0x10, top + j * 0x10, 0x10, 0x10, -8, -8, side, false, 0, 0, 0x70, (h - 1 - j) * 2 + (w - 1 - i) * h * 2);
            }
        }
    }
}

int CollapsingPlatform::OnLeaveScreen() {
    f = -1;
    return 1;
}

void CollapsingPlatform::Render(int CamX, int CamY) {
    if (!SolidTop) return;

    if (Scene->ZoneID == 1) {
        G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX);
    }
    else if (CurrentAnimation >= 0) {
        G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX);
    }
    else {
        G->DrawRectangle(X - W / 2 - CamX, Y - H / 2 - CamY, W, H, 0xFF0000);
    }
    }

int CollapsingPlatform::CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough) {
    if (!checkJumpThrough) return 0;

    if (!SolidTop) return 0;

    if (Scene->ZoneID == 1) {
        if (!FlipX) {
            if (probeX >= X - W / 2 && probeY >= Y - H / 2 && probeX < X && probeY < Y + H / 2) {
                if (f == -1 && Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->AngleMode == 0 && Scene->Players[PlayerID]->EZY < Y - H / 2) {
                    f = 60 + Allotted;
                    Priority = true;
                }

                return 1;
            }

            if (probeX >= X && probeY >= Y - H / 2 + (probeX - X) / 3 && probeX < X + W / 2 && probeY < Y + H / 2) {
                if (f == -1 && Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->AngleMode == 0 && Scene->Players[PlayerID]->EZY < Y - H / 2) {
                    f = 60 + Allotted;
                    Priority = true;
                }

                return 1;
            }

        }
        else if (FlipX) {
            if (probeX >= X && probeY >= Y - H / 2 && probeX < X + W / 2 && probeY < Y + H / 2) {
                if (f == -1 && Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->AngleMode == 0 && Scene->Players[PlayerID]->EZY < Y - H / 2) {
                    f = 60 + Allotted;
                    Priority = true;
                }

                return 1;
            }

            if (probeX >= X - W / 2 && probeY >= Y - H / 2 + (X - probeX) / 3 && probeX < X && probeY < Y + H / 2) {
                if (f == -1 && Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->AngleMode == 0 && Scene->Players[PlayerID]->EZY < Y - H / 2) {
                    f = 60 + Allotted;
                    Priority = true;
                }

                return 1;
            }

        }

    }
    else {
        if (probeX >= X - W / 2 && probeY >= Y - H / 2 && probeX < X + W / 2 && probeY < Y + H / 2) {
            if (f == -1 && Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->AngleMode == 0 && Scene->Players[PlayerID]->EZY < Y - H / 2) {
                f = 60 + Allotted;
                Priority = true;
            }

            return 1;
        }

    }
    return 0;
}


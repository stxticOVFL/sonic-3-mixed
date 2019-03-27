// Object ID: 0x04
// Object Name: CollapsingPlatform.cpp

#include "CollapsingPlatform.h"

typedef IMath Math;

CONSTRUCTER CollapsingPlatform::CollapsingPlatform() {
    if (LevelScene::IsZoneCurrently("AIZ")) {
        Act1BinIndex = LevelScene::LoadSpriteBin("AIZ/Collapsing Platform.bin");
        Act2BinIndex = LevelScene::LoadSpriteBin("AIZ/Collapsing Platform 2.bin");
        BinIndex = Act1BinIndex;
    }
    else if (LevelScene::IsZoneCurrently("ICZ")) {
        BinIndex = LevelScene::LoadSpriteBin("ICZ/Collapsing Bridge 1.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/Collapsing Platform.bin");
        Act1BinIndex = BinIndex;
        Act2BinIndex = BinIndex;
    }
}

void CollapsingPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    W = 48;
    H = 32;
    f = -1;
    Allotted = 60 * 5;
    Separation = 2;
    Sections = 8;
    Vsect = 2;
    CurrentAnimation = -1;
    Outliner = Scene->AddNewObject(Obj_PlatformOutliner, 0, X, Y, false, false);
    Outliner->Parent = this;
    SolidTop = true;
    SolidCustomized = true;
    Scene->AddSelfToRegistry(this, "Solid");
    switch (Scene->ZoneID) {
        case 1:
        W = 0x30;
        H = 0x20;
        if (Scene->Act == 2) {
            H = 0x18;
        }

        if (Scene->Act == 2) {
            BinIndex = Act2BinIndex;
            Sprite = LevelScene::GetSpriteFromBinIndex(BinIndex);
            Sprite->LinkPalette(Scene->TileSprite);
            CurrentAnimation = Sprite->FindAnimation("Collapsing Platform 2");
        }
        else if (Scene->Act == 1) {
            BinIndex = Act1BinIndex;
            CurrentAnimation = Sprite->FindAnimation("Collapsing Platform");
        }
        else {
            CurrentAnimation = 0;
        }
        Frame = 0;
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        W = 0x30;
        H = 0x2C;
        CurrentAnimation = Sprite->FindAnimation("Collapsing Bridge 1");
        Sprite->LinkPalette(Scene->TileSprite);
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
        break;
        case 9:
        break;
        case 10:
        break;
        case 11:
        break;
        case 12:
        break;
        case 13:
        break;
        case 14:
        break;
    }

    VisW = W;
    VisH = H * 2 + 16;
    W <<= 1;
    H <<= 1;
}

void CollapsingPlatform::Update() {
    if (!Scene->maxLayer && !isHeldDebugObject) {
        Outliner->W = Sprite->Animations[CurrentAnimation].Frames[Frame].W;
        Outliner->H = Sprite->Animations[CurrentAnimation].Frames[Frame].H;
        Outliner->Visible = true;
    }
    else {
        Outliner->Visible = false;
    }
    SolidTop = true;
    if (f > -1 && f <= Allotted) {
        SolidTop = false;
        Solid = false;
        if (f == Allotted) {
            Break();
        }

    }

    if (f > 0) {
        f -= 1;
    }

    Object::Update();
}

void CollapsingPlatform::Break() {
    Sound::Play(Sound::SFX_COLLAPSE);
    if (!Sprite) return;

    if (CurrentAnimation < 0) return;

    int x = X + Sprite->Animations[CurrentAnimation].Frames[Frame].OffX + 8;
    int y = Y + Sprite->Animations[CurrentAnimation].Frames[Frame].OffY + 8;
    int w = Sprite->Animations[CurrentAnimation].Frames[Frame].W >> 4;
    int h = Sprite->Animations[CurrentAnimation].Frames[Frame].H >> 4;
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
    if (!Visible) {
        return;
    }

    if (!SolidTop) {
        return;
    }

    if (CurrentAnimation >= 0) {
        if (Scene->ZoneID == 1) {
            G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX);
        }
        else {
            G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX);
        }
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


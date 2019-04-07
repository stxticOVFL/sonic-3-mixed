// Object ID: 0x2C
// Object Name: CollapsingLogBridge.cpp

#include "CollapsingLogBridge.h"

typedef IMath Math;

CONSTRUCTER CollapsingLogBridge::CollapsingLogBridge() {
    BinIndex = LevelScene::LoadSpriteBin("AIZ/Collapsing Log Bridge.bin");
}

void CollapsingLogBridge::Create() {
    Solid::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    W = 180;
    H = 16;
    VisW = 116;
    VisH = 16;
    SolidTop = true;
    SolidCustomized = true;
    Drawbridge = false;
    CurrentAnimation = Sprite->FindAnimation("Collapsing Log Bridge");
    if (SubType & 0x80) {
        VisualLayer = 1;
        Drawbridge = true;
        CurrentAnimation = 13;
        W = 192;
        H = 16;
    }

    Allotted = SubType & 0x7F;
    Frame = -1;
}

void CollapsingLogBridge::Update() {
    if (Frame > -1 && Frame <= 60) {
        SolidTop = false;
        if (Frame == 60) Break();

    }

    if (Frame > 0) Frame -= 1;

    if (Scene->Signal[0] && Drawbridge) {
        Scene->Signal[0] = 0;
        Break();
    }

    Object::Update();
}

void CollapsingLogBridge::Break() {
    Sound::Play(Sound::SFX_COLLAPSE);
    Active = false;
    int i = 0;
    int L0 = Sprite->Animations[CurrentAnimation].Frames[0].X;
    int T0 = Sprite->Animations[CurrentAnimation].Frames[0].Y;
    int L1 = Sprite->Animations[CurrentAnimation].Frames[1].X;
    int T1 = Sprite->Animations[CurrentAnimation].Frames[1].Y;
    int L2 = Sprite->Animations[CurrentAnimation].Frames[2].X;
    int T2 = Sprite->Animations[CurrentAnimation].Frames[2].Y;
    int X0 = X + Sprite->Animations[CurrentAnimation].Frames[0].OffX;
    int Y0 = Y + Sprite->Animations[CurrentAnimation].Frames[0].OffY;
    int Y2 = Y + Sprite->Animations[CurrentAnimation].Frames[2].OffY;
    int W0 = Sprite->Animations[CurrentAnimation].Frames[0].W;
    int H0 = Sprite->Animations[CurrentAnimation].Frames[0].H;
    int H2 = Sprite->Animations[CurrentAnimation].Frames[2].H;
    if (Drawbridge) {
        Scene->AddMovingSprite(Sprite, X0 - 80 + i * 32, Y0, L1, T1, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 80 + i * 32, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 80 + i * 32, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 80 + i * 32, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 80 + i * 32, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 80 + i * 32, Y2, L2, T2, W0, H2, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
    }
    else {
        Scene->AddMovingSprite(Sprite, X0 - 75 + i * 30, Y0, L1, T1, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 75 + i * 30, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 75 + i * 30, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 75 + i * 30, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 75 + i * 30, Y0, L0, T0, W0, H0, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
        Scene->AddMovingSprite(Sprite, X0 - 75 + i * 30, Y2, L2, T2, W0, H2, 0, 0, false, false, 0, 0, 0x70, i * 8);
        i++;
    }
}

void CollapsingLogBridge::Render(int CamX, int CamY) {
    if (Drawbridge) {
        G->DrawSprite(Sprite, CurrentAnimation, 1, X - CamX - 80, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX - 48, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX - 16, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX + 16, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX + 48, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 2, X - CamX + 80, Y - CamY, 0, IE_NOFLIP);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, 1, X - CamX - 75, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX - 45, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX - 15, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX + 15, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX + 45, Y - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, 2, X - CamX + 75, Y - CamY, 0, IE_NOFLIP);
    }
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int CollapsingLogBridge::CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough) {
    if (!checkJumpThrough) return 0;

    if (!SolidTop) return 0;

    if (probeX >= X - W / 2 && probeY >= Y - H / 2 && probeX < X + W / 2 && probeY < Y + H / 2) {
        if (!Drawbridge && Frame == -1 && Scene->Players[PlayerID]->Ground && Scene->Players[PlayerID]->AngleMode == 0 && Scene->Players[PlayerID]->EZY < Y - H / 2) {
            Frame = 60 + Allotted;
        }

        return 1;
    }

    return 0;
}


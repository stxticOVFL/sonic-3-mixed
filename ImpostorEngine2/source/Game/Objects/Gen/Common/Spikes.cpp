// Object ID: 0x08
// Object Name: Spikes.cpp

#include "Spikes.h"

typedef IMath Math;

CONSTRUCTER Spikes::Spikes() {
    if (SaveGame::CurrentMode == 0) {
        BinIndex = LevelScene::LoadSpriteBin("GlobalS3K/Spikes.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("Global/Spikes.bin");
    }
}

void Spikes::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Rotation = 0;
    Size = 1 + (SubType & 0x30) / 0x10;
    Vertical = (SubType >> 6) & 0x1;
    In = false;
    W = 32 * Size;
    H = 32;
    Y = InitialY;
    Timer = 0;
    CleanupInactiveObject = true;
    if (Vertical && FlipX) {
        W = 32;
        H = 32 * Size;
        Rotation = 0x40;
    }

    if (Vertical && !FlipX) {
        W = 32;
        H = 32 * Size;
        Rotation = 0xC0;
    }

    if (!Vertical && FlipY) {
        W = 32 * Size;
        H = 32;
        Rotation = 0x80;
    }

    if ((SubType & 0xF) == 0x1) {
        if (FlipY) {
            Y += 32;
        }

    }

    if (!((SubType & 0xF) == 0x1 || (SubType & 0xF) == 0x2)) In = true;

    CurrentAnimation = Sprite->FindAnimation("Spikes V");
}

void Spikes::Update() {
    if ((SubType & 0xF) == 0x1 || (SubType & 0xF) == 0x2) {
        Timer++;
        Timer &= 0x3F;
        if (Timer >= 60) {
            if (Timer == 60) In = !In;

            if (In) {
                X += Math::sinHex(Rotation) >> 13;
                Y += Math::cosHex(Rotation) >> 13;
                Y += 1;
            }
            else {
                X -= Math::sinHex(Rotation) >> 13;
                Y -= Math::cosHex(Rotation) >> 13;
                Y -= 1;
            }
        }

    }

    Object::Update();
}

void Spikes::Render(int CamX, int CamY) {
    int flag = IE_NOFLIP;
    if (Rotation == 0xC0) {
        flag = IE_FLIPX;
    }

    for (int i = 0; i < Size; i++)
{
        if (Vertical) {
            G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY - (Size - 1) * 16 + i * 32, Rotation, flag);
        }
        else {
            G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX - (Size - 1) * 16 + i * 32, Y - CamY, Rotation, flag);
        }
    }
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Spikes::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (HitFrom == CollideSide::TOP && Rotation == 0 && Scene->Players[PlayerID]->YSpeed >= 0) {
        Scene->Players[PlayerID]->Hurt(X, true);
    }
    else if (HitFrom == CollideSide::BOTTOM && Rotation == 180 && Scene->Players[PlayerID]->YSpeed <= 0 && !In && ((SubType & 0xF) == 0x1 || (SubType & 0xF) == 0x2)) {
        Scene->Players[PlayerID]->Hurt(X, true);
    }
    else if (HitFrom == CollideSide::BOTTOM && Rotation == 180 && Scene->Players[PlayerID]->YSpeed <= 0 && In && !((SubType & 0xF) == 0x1 || (SubType & 0xF) == 0x2)) {
        Scene->Players[PlayerID]->Hurt(X, true);
        Scene->Players[PlayerID]->EZY += 6;
    }
    else if ((Rotation == 90 && HitFrom == CollideSide::LEFT) || (Rotation == 270 && HitFrom == CollideSide::RIGHT)) {
        if (Scene->Players[PlayerID]->EZY + 20 - 4 - 4 <= Y - 16) {
            return 0;
        }

        Scene->Players[PlayerID]->Hurt(X, true);
    }

    return 1;
}


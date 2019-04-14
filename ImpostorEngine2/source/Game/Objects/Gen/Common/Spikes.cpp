// Object ID: 0x08
// Object Name: Spikes.cpp

#include "Spikes.h"

typedef IMath Math;

void Spikes::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    Rotation = 0;
    In = false;
    Sprite = LevelScene::LoadSpriteFromBin("Global/Spikes.bin", SaveGame::CurrentMode);
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    AttributeBuffer = GetAttribute("type");
    Type = AttributeBuffer.ValVar;
    AttributeBuffer = GetAttribute("moving");
    Moving = AttributeBuffer.ValBool;
    AttributeBuffer = GetAttribute("count");
    Count = AttributeBuffer.ValUint8;
    AttributeBuffer = GetAttribute("stagger");
    Stagger = AttributeBuffer.ValUint8;
    AttributeBuffer = GetAttribute("timer");
    TimerMax = AttributeBuffer.ValUint8;
    AttributeBuffer = GetAttribute("planeFilter");
    PlaneFilter = AttributeBuffer.ValUint8;
    AttributeBuffer = GetAttribute("in");
    In = AttributeBuffer.ValBool;
    W = 32 * Count;
    H = 32;
    Y = InitialY;
    Vertical = 0;
    Timer = 0;
    CleanupInactiveObject = true;
    if (Type == 2) {
        W = 32;
        H = 32 * Count;
        Rotation = 0x40;
        Vertical = 1;
    }

    if (Type == 3) {
        W = 32;
        H = 32 * Count;
        Rotation = 0xC0;
        Vertical = 1;
    }

    if (Type == 1) {
        W = 32 * Count;
        H = 32;
        Rotation = 0x80;
    }

    CurrentAnimation = Sprite->FindAnimation("Spikes V");
}

void Spikes::Update() {
    if (Moving) {
        Timer++;
        Timer &= 0x3F;
        if (Timer >= TimerMax) {
            if (Timer == TimerMax) In = !In;

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

    for (int i = 0; i < Count; i++)
{
        if (Vertical) {
            G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY - (Count - 1) * 16 + i * 32, Rotation, flag);
        }
        else {
            G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX - (Count - 1) * 16 + i * 32, Y - CamY, Rotation, flag);
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


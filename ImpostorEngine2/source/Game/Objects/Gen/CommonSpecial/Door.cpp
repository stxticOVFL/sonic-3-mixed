// Object ID: 0x3C
// Object Name: Door.cpp

#include "Door.h"

typedef IMath Math;

void Door::Create() {
    Object::Create();
    this->W = 32;
    this->H = 64;
    this->Active = true;
    this->Priority = false;
    this->Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Horizontal = (SubType & 0x80) == 0x80;
    DoorType = (SubType & 0xF);
    if (DoorType == 0) {
        W = 32;
    }
    else if (DoorType == 1) {
        W = 16;
    }
    else if (DoorType == 2) {
        W = 16;
    }

    if (Horizontal) {
        W = 64;
        H = 16;
    }

    if (!Horizontal) {
        if (Scene->Player->EZX - 10 < this->X + W / 2) this->Y = this->InitialY - 64;
        else this->Y = this->InitialY;
    }
    else {
        if (Scene->Player->EZY + Scene->Player->H / 2 > this->Y + H / 2) {
            if (FlipX) this->X = this->InitialX - 64;
            else this->X = this->InitialX + 64;
        }
        else {
            this->X = this->InitialX;
        }
    }
}

void Door::Update() {
    bool AllPast = true;
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (!Horizontal) {
            if (Scene->Players[i]->EZX - 10 < this->X + W / 2 && Scene->Players[i]->OnScreen) {
                AllPast = false;
                break;
            }

        }
        else {
            if (Scene->Player->EZY + Scene->Player->H / 2 > this->Y + H / 2 && Scene->Players[i]->OnScreen) {
                AllPast = false;
                break;
            }

        }
    }
    if (!AllPast) {
        if (!Horizontal) {
            if (this->Y > this->InitialY - 64) this->Y -= 8;

        }
        else {
            if (FlipX) {
                if (this->X > this->InitialX - 64) this->X -= 8;

            }
            else {
                if (this->X < this->InitialX + 64) this->X += 8;

            }
        }
    }
    else {
        if (!Horizontal) {
            if (this->Y < this->InitialY) this->Y += 8;

        }
        else {
            if (FlipX) {
                if (this->X < this->InitialX) this->X += 8;

            }
            else {
                if (this->X > this->InitialX) this->X -= 8;

            }
        }
    }
    Object::Update();
}

void Door::Render(int CamX, int CamY) {
    if (Scene->ZoneID == 2) {
        G->DrawSprite(Scene->TileSprite, 0, 0x8B, 8 + this->X - CamX + (-16), 8 + this->Y - 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8C, 8 + this->X - CamX + (0), 8 + this->Y - 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8D, 8 + this->X - CamX + (-16), 8 + this->Y - 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8E, 8 + this->X - CamX + (0), 8 + this->Y - 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8B, 8 + this->X - CamX + (-16), 8 + this->Y + 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8C, 8 + this->X - CamX + (0), 8 + this->Y + 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8D, 8 + this->X - CamX + (-16), 8 + this->Y + 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8E, 8 + this->X - CamX + (0), 8 + this->Y + 16 - CamY + (0), 0, IE_NOFLIP);
    }
    else {
        G->DrawRectangle(X - CamX - W / 2, Y - CamY - H / 2, W, H, 0xFFFFFF);
    }
    }


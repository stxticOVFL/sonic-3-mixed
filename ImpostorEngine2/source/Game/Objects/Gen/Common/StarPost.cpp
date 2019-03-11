// Object ID: 0x34
// Object Name: StarPost.cpp

#include "StarPost.h"

typedef IMath Math;

void StarPost::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = false;
    W = 16;
    H = 64;
    Rotation = 0;
    Activated = false;
    Spin = 0;
    Blinking = false;
    this->Frame = 0;
    CleanupInactiveObject = true;
    ShowStars = false;
    StarTimer = 0x400;
}

void StarPost::Update() {
    if (!isHeldDebugObject) {
        for (int i = 0; i < 20; i++)
{
            if (Scene->CollisionAt(this->X, this->Y + H / 2 - 1)) {
                this->Y -= 1;
            }

        }
        if (Scene->Checkpoint > this->SubType) this->Blinking = true;

        if (this->Activated && this->Spin < 32) this->Spin++;

        if (this->Spin == 32) this->Blinking = true;

        if (this->Blinking) this->Frame = ((Scene->Frame >> 2) & 0x1);

        if (ShowStars) {
            if (StarTimer > 0) {
                StarTimer--;
            }
            else {
                StarTimer = 0;
                ShowStars = false;
            }
        }

    }

    Object::Update();
}

int StarPost::OnLeaveScreen() {
    if (this->Activated && this->Spin < 32) this->Spin = 32;

    return 1;
}

void StarPost::DrawStar(int Rock, int Ang, int Side, int CamX, int CamY) {
    int cosval = (Math::cosHex(Rock) * 16) >> 16;
    int xx = (cosval * Math::cosHex(Ang)) >> 16;
    int yy = (cosval * Math::sinHex(Ang)) >> 16;
    if (Math::sinHex(Rock) * Side >= 0) {
        G->DrawSprite(Sprite, Sprite->Animations[13].Frames[0].X, Sprite->Animations[13].Frames[0].Y, Sprite->Animations[13].Frames[0].W, Sprite->Animations[13].Frames[0].H, X - CamX + xx, Y - CamY + yy, 0, IE_NOFLIP, Sprite->Animations[13].Frames[0].OffX, Sprite->Animations[13].Frames[0].OffY);
    }

}

void StarPost::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 8, 0, this->X - CamX, this->Y - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 9 + Frame, Frame, this->X - CamX + (Math::sinHex(this->Spin << 4) >> 13), this->Y - CamY - 16 - (Math::cosHex(this->Spin << 4) >> 13), 0, IE_NOFLIP);
    if (ShowStars) {
        G->DrawSprite(Sprite, 8 + 5, 0, this->X - CamX, (this->Y - 40) - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, 8 + 5, 0, this->X - CamX, (this->Y - 40) - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, 8 + 5, 0, this->X - CamX, (this->Y - 40) - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, 8 + 5, 0, this->X - CamX, (this->Y - 40) - CamY, 0, IE_NOFLIP);
    }

    }

int StarPost::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!this->Blinking) this->Activated = true;

    if (Scene->Checkpoint < this->SubType) {
        Scene->Checkpoint = this->SubType;
        Scene->SavedPositionX = X;
        Scene->SavedPositionY = Y + H / 2 - 16;
        if (Scene->Players[PlayerID]->Rings >= 25) {
            if (StarTimer > 0) ShowStars = true;

        }

        Sound::Play(Sound::SFX_STARPOST);
    }

    return 1;
}


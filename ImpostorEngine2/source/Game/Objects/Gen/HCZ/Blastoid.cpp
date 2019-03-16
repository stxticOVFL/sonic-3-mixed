// Object ID: 0x94
// Object Name: Blastoid.cpp

#include "Blastoid.h"

typedef IMath Math;

void Blastoid::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 0;
    HitCount = 1;
    this->Y += 1;
    ShotIndex = 0;
    for (int i = 0; i < 8; i++)
{
        Children[i] = Scene->AddNewObject(Obj_BlastoidShot, 0, 0, 0, false, false);
        Children[i]->Sprite = Sprite;
        Children[i]->CurrentAnimation = CurrentAnimation + 1;
    }
}

int Blastoid::OnHit() {
    Scene->LevelTriggerFlag |= 1 << SubType;
    return OnDeath();
}

void Blastoid::Update() {
    if (Math::abs(Scene->Player->EZX - X) < 128) {
        if ((Scene->Timer & 0x7F) == 0x00 || (Scene->Timer & 0x7F) == 0x10 || (Scene->Timer & 0x7F) == 0x20) {
            if (FlipX) {
                Children[ShotIndex]->X = X + 18;
                Children[ShotIndex]->XSpeed = 0x200;
            }
            else {
                Children[ShotIndex]->X = X - 18;
                Children[ShotIndex]->XSpeed = -0x200;
            }
            Children[ShotIndex]->Y = Y - 8;
            Children[ShotIndex]->YSpeed = -0x100;
            Children[ShotIndex]->Timer = ShotIndex & 1;
            ShotIndex++;
            ShotIndex &= 0x7;
            Frame = 0;
            Sound::Play(Sound::SFX_SHOT);
        }

    }

    if (this->Sprite->Animations[this->CurrentAnimation].AnimationSpeed > 2) this->Frame += this->Sprite->Animations[this->CurrentAnimation].AnimationSpeed;
    else if (this->Sprite->Animations[this->CurrentAnimation].Frames[Frame >> 8].Duration != 0) this->Frame += 0x100 / this->Sprite->Animations[this->CurrentAnimation].Frames[this->Frame >> 8].Duration;

    if (this->Frame >= this->Sprite->Animations[this->CurrentAnimation].FrameCount << 8) this->Frame = this->Sprite->Animations[this->CurrentAnimation].FrameToLoop << 8;

    Object::Update();
}

void Blastoid::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


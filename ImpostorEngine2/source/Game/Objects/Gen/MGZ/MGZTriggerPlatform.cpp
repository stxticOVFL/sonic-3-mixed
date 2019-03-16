// Object ID: 0x57
// Object Name: MGZTriggerPlatform.cpp

#include "MGZTriggerPlatform.h"

typedef IMath Math;

void MGZTriggerPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    PlatformType = SubType >> 4;
    TriggerID = SubType & 0xF;
    W = 64;
    H = 128;
    if (PlatformType == 0) {
        W = 0x80;
        H = 0x40;
    }

    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
}

void MGZTriggerPlatform::Update() {
    if (PlatformType > 0) {
        if ((Scene->LevelTriggerFlag >> TriggerID) & 1) {
            Scene->ShakeTimer = 0;
            if (FlipX) {
                if (Y + (SubType & 0xF0) * 4 > InitialY) {
                    Y -= SubType >> 4;
                    Scene->ShakeTimer = -1;
                    if (!(Scene->Frame & 0xF)) {
                        Sound::Play(Sound::SFX_RUMBLE);
                    }

                }
                else if (Y == InitialY - (SubType & 0xF0) * 4) {
                    Scene->LevelTriggerFlag &= (1 << TriggerID);
                }

            }
            else {
                if (Y < InitialY + (SubType & 0xF0) * 4) {
                    Y += SubType >> 4;
                    Scene->ShakeTimer = -1;
                    if (!(Scene->Frame & 0xF)) {
                        Sound::Play(Sound::SFX_RUMBLE);
                    }

                }
                else if (Y == InitialY + (SubType & 0xF0) * 4) {
                    Scene->LevelTriggerFlag &= (1 << TriggerID);
                }

            }
        }

        if (((Scene->LevelTriggerFlag >> TriggerID) & 1) && Math::abs(X - Scene->Player->EZX) >= 0x1D0) {
            Y = InitialY;
        }

    }
    else {
        if (((Scene->LevelTriggerFlag >> TriggerID) & 1)) {
            Scene->ShakeTimer = 0;
            if (FlipX) {
                if (X > InitialX - 0x80) {
                    X -= 2;
                    Scene->ShakeTimer = -1;
                    if (!(Scene->Frame & 0xF)) {
                        Sound::Play(Sound::SFX_RUMBLE);
                    }

                }
                else if (X == InitialX - 0x80) {
                    Scene->LevelTriggerFlag &= (1 << TriggerID);
                    Active = false;
                }

            }
            else {
                if (X < InitialX + 0x80) {
                    X += 2;
                    Scene->ShakeTimer = -1;
                    if (!(Scene->Frame & 0xF)) {
                        Sound::Play(Sound::SFX_RUMBLE);
                    }

                }
                else if (X == InitialX + 0x80) {
                    Scene->LevelTriggerFlag &= (1 << TriggerID);
                    Active = false;
                }

            }
        }

    }
    Object::Update();
}

void MGZTriggerPlatform::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 6, Math::sign(PlatformType), X - CamX, Y - CamY, 0, FlipY ? IE_FLIPY : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


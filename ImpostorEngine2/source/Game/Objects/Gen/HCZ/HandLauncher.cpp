// Object ID: 0x3A
// Object Name: HandLauncher.cpp

#include "HandLauncher.h"

typedef IMath Math;

void HandLauncher::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    CurrentAnimation = 4;
    Near = false;
    Spinning = false;
    Timer = -1;
    outY = 0;
    outY2 = 0;
    coolDown = -1;
    lastOutY2 = -1;
}

void HandLauncher::Update() {
    Near = false;
    Spinning = false;
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (Scene->Players[i]->EZX >= X - 32 && Scene->Players[i]->EZX < X + 32 && ((Scene->Players[i]->EZY + Scene->Players[i]->H / 2 >= Y - 32 && Scene->Players[i]->EZY + Scene->Players[i]->H / 2 <= Y + 9) || Scene->Players[i]->ObjectControlled != 0)) {
            Near = true;
        }

        if (Scene->Players[i]->EZX >= X - 8 && Scene->Players[i]->EZX < X + 8 && Scene->Players[i]->EZY + Scene->Players[i]->H / 2 >= Y - 32 && Scene->Players[i]->EZY + Scene->Players[i]->H / 2 <= Y + 9) {
            Spinning = true;
        }

    }
    if (Spinning) {
        if (Sprite->Animations.size() > CurrentAnimation) {
            if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 2) Frame += Sprite->Animations[CurrentAnimation].AnimationSpeed;
            else if (Sprite->Animations[CurrentAnimation].Frames[Frame / 0x100].Duration != 0) Frame += 0x100 / Sprite->Animations[CurrentAnimation].Frames[Frame / 0x100].Duration;

            if (Frame / 0x100 >= Sprite->Animations[CurrentAnimation].FrameCount - 1) {
                Frame = Sprite->Animations[CurrentAnimation].FrameToLoop * 0x100;
            }

        }

    }
    else {
        Frame = 0;
    }
    lastOutY2 = outY2;
    if (Timer > 0) {
        outY2 += (24 - outY2) / 3;
        Timer -= 1;
    }

    if (Near) {
        outY += (56 - outY) / 3;
    }
    else {
        outY += (0 - outY) / 3;
    }
    if (outY == 1) outY = 0;

    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (Scene->Players[i]->Action == ActionType::Hurt || Scene->Players[i]->Action == ActionType::Dead) continue;

        if (Math::abs(Scene->Players[i]->X - X) < 0x8 && Math::abs(Scene->Players[i]->GroundSpeed) < 0x400 && (Scene->Players[i]->Y + Scene->Players[i]->H / 2) >= Y - 0x4 && Scene->Players[i]->Y + Scene->Players[i]->H / 2 <= Y + 0x9) {
            if (Scene->Players[i]->ObjectControlled == 0) {
                Scene->Players[i]->ObjectControlled = 0x7F;
                Timer = 60;
                Sound::Play(Sound::SFX_ROLL);
                Scene->Players[i]->Vibrate(VibrationType::SpindashRev);
            }

        }

        if (Timer > 0 && Scene->Players[i]->ObjectControlled != 0) {
            Scene->Players[i]->GroundSpeed = 0x1000 * (FlipX ? -1 : 1);
            Scene->Players[i]->X = X;
            Scene->Players[i]->DisplayX = Scene->Players[i]->X;
            Scene->Players[i]->H = 10;
            Scene->Players[i]->Y = Y + 64 - outY - lastOutY2 - Scene->Players[i]->OrigH / 2;
            Scene->Players[i]->DisplayY = Scene->Players[i]->Y;
            Scene->Players[i]->YSpeed = 0;
            Scene->Players[i]->DisplayFlip = (FlipX ? -1 : 1);
            Scene->Players[i]->Action = ActionType::Normal;
            Scene->Players[i]->Ground = true;
        }

        if (Timer == 0 && coolDown == -1 && Scene->Players[i]->ObjectControlled != 0) {
            Scene->Players[i]->Y = Y + 10 - Scene->Players[i]->OrigH / 2;
            Scene->Players[i]->DisplayY = Scene->Players[i]->Y;
            Scene->Players[i]->Action = ActionType::Normal;
            Scene->Players[i]->Ground = true;
            Scene->Players[i]->ObjectControlled = 0;
            Scene->Players[i]->H = Scene->Players[i]->OrigH;
            Sound::Play(Sound::SFX_SPINDASH);
        }

    }
    if (Timer == 0 && coolDown == -1) {
        coolDown = 30;
    }

    if (coolDown > -1) {
        outY2 += (0 - outY2) / 3;
        coolDown -= 1;
    }

    if (coolDown == 0) {
        Timer = -1;
        coolDown = -1;
    }

    Object::Update();
}

void HandLauncher::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY + 64 - outY - lastOutY2, 0, IE_NOFLIP);
    if (Timer > 0) {
        G->DrawSprite(Sprite, 6, 0, X - CamX, Y - CamY + 68 - outY - lastOutY2, 0, IE_NOFLIP);
    }
    else if (Near) {
        G->DrawSprite(Sprite, 5, 0, X - CamX, Y - CamY + 64 - outY - lastOutY2, 0, IE_NOFLIP);
    }

    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


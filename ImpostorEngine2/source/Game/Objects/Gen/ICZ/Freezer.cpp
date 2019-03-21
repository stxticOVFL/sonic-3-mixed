// Object ID: 0xB2
// Object Name: Freezer.cpp

#include "Freezer.h"

typedef IMath Math;

CONSTRUCTER Freezer::Freezer() {
}

void Freezer::Create() {
    Object::Create();
    W = 32;
    H = 24;
    Solid = false;
    FreezeTimer = 0;
    CurrentAnimation = Sprite->FindAnimation("Freezer");
    DustAnimation = Sprite->FindAnimation("Particles");
    IceCubeAnimation = Sprite->FindAnimation("Player Ice Cube");
    VisualLayer = 1;
    FreezeTimer = 0;
    OnOff = true;
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        Frozen[i] = false;
        FrozenTimer[i] = 0;
    }
    Range = 0;
}

void Freezer::Update() {
    FreezeTimer = OnOff ? (FreezeTimer > 50 ? 50 : FreezeTimer + 1) : (FreezeTimer < 0 ? 0 : FreezeTimer - 1);
    WaitTimer = WaitTimer == 0 ? (FreezeTimer == 50 || FreezeTimer == 0 ? Math::randRange(20, 60) : 0) : WaitTimer - 1;
    OnOff = WaitTimer == 0 ? (OnOff ? (FreezeTimer == 50 ? false : true) : (FreezeTimer == 0 ? true : false)) : OnOff;
    Range = FreezeTimer * 2;
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if ((Scene->Players[i]->Y >= Y && Scene->Players[i]->Y <= Y + Range && Scene->Players[i]->X >= X - 16 && Scene->Players[i]->X <= X + 16) && (!Frozen[i] && FrozenTimer[i] == 0) && (Range != 0)) {
            if (Scene->Players[i]->Shield != ShieldType::Fire) {
                Frozen[i] = true;
                FrozenTimer[i] = 80;
                Scene->Players[i]->ControlLocked = true;
                Scene->Players[i]->InputLockLeftRight = true;
                Scene->Players[i]->AnimationStop = true;
                StoredX[i] = Scene->Players[i]->X;
                StoredY[i] = Scene->Players[i]->Y;
                StoredFrame[i] = Scene->Players[i]->Frame;
            }

        }

        if (Frozen[i]) {
            Scene->Players[i]->X = StoredX[i];
            Scene->Players[i]->Y = StoredY[i];
            Scene->Players[i]->ChangeAnimation(18);
            Scene->Players[i]->XSpeed = 0;
            Scene->Players[i]->YSpeed = 0;
        }

        FrozenTimer[i] = FrozenTimer[i] <= 0 ? 0 : FrozenTimer[i] - 1;
        if (Frozen[i] && FrozenTimer[i] == 0) {
            Scene->Players[i]->ControlLocked = false;
            Scene->Players[i]->AnimationStop = false;
            Scene->Players[i]->InputLockLeftRight = false;
            Scene->Players[i]->Hurt(Scene->Players[i]->X, false);
            Frozen[i] = false;
            FrozenTimer[i] = 80;
        }

    }
    Object::Update();
}

void Freezer::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
    for (int i = 0; i < FreezeTimer / 10; i++)
{
        G->DrawSprite(Sprite, DustAnimation, Math::ceil((float)(i / 1.5)) + 13, X - CamX + Math::randRange(10, -10) - 20, Y + (i * 20) - CamY + Math::randRange(10, -10), Math::randRange(10, -10), IE_NOFLIP);
    }
    for (int i = 0; i < 8; i++)
{
        if (Frozen[i]) {
            G->DrawSprite(Sprite, IceCubeAnimation, Frame, StoredX[i] - CamX, StoredY[i] - CamY, 0, IE_NOFLIP);
        }

    }
    }


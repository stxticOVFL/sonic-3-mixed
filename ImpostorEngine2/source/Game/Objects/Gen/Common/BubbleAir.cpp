// Object ID: 0xFFFFFFFF
// Object Name: BubbleAir.cpp

#include "BubbleAir.h"

typedef IMath Math;

void BubbleAir::Create() {
    Object::Create();
    W = 16;
    H = 16;
    Active = true;
    Priority = false;
    Frame = 0;
    CurrentAnimation = Math::randRange(3, 5);
    Sprite = Scene->WaterSprite;
    VisualLayer = 1;
    AutoAnimate = true;
    YSpeed = -0x88;
    Timer = 0;
}

void BubbleAir::Update() {
    X = ((Math::sinHex(Timer << 1) * 3) >> 16) + InitialX;
    Timer++;
    Timer &= 0x7F;
    if (Y < Scene->WaterLevel) Active = false;

    Object::Update();
}

void BubbleAir::OnAnimationFinish() {
}

int BubbleAir::OnLeaveScreen() {
    Active = false;
    return 0;
}

void BubbleAir::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int BubbleAir::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (CurrentAnimation != 3) return false;

    if (Frame < 13) return false;

    App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);
    Scene->Players[PlayerID]->UnderwaterTimer = 1800;
    Scene->Players[PlayerID]->GroundSpeed = 0;
    Scene->Players[PlayerID]->XSpeed = 0;
    Scene->Players[PlayerID]->YSpeed = 0;
    Sound::Play(Sound::SFX_AIR_BUBBLE);
    Scene->AddExplosion(Sprite, 6, false, X, Y, VisualLayer);
    Active = false;
    return 1;
}


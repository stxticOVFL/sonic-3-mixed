// Object ID: 0x6C
// Object Name: TensionBridge.cpp

#include "TensionBridge.h"

typedef IMath Math;

void TensionBridge::Create() {
    Object::Create();
    this->W = 128;
    this->H = 24;
    this->Active = true;
    this->Priority = false;
    Frame = 0;
    CurSegment = 0;
    Count = SubType & 0x7F;
    Angled = ((SubType & 0x80) / 0x80) * 3;
    if (Scene->ZoneID != 5) {
        Angled = 0;
    }

    Triggered = (SubType & 0x80) == 0x80;
    switch (Scene->ZoneID) {
        case 2:
        CurrentAnimation = 18;
        break;
        case 5:
        CurrentAnimation = Sprite->FindAnimation("Tension Bridge");
        break;
    }

    MaxDepress = 2;
    for (int i = 0; i < Count; i++)
{
        Children[i] = Scene->AddNewObject(Obj_TensionBridgeChild, i, X - Count * 8 + i * 16, Y + i * Angled, false, false);
        Children[i]->Timer = MaxDepress;
        Children[i]->Sprite = Sprite;
        Children[i]->CurrentAnimation = CurrentAnimation;
        if (i * 2 == Count - 2) {
        }
        else if (i < Count / 2) {
            MaxDepress += 2;
        }
        else if (i >= Count / 2) {
            MaxDepress -= 2;
        }

    }
    Broken = false;
    Timer = -1;
    if (Scene->ZoneID == 2) {
        BrakeIndexes[0] = 7;
        BrakeIndexes[1] = 6;
        BrakeIndexes[2] = 4;
        BrakeIndexes[3] = 0;
        BrakeIndexes[4] = 5;
        BrakeIndexes[5] = 2;
        BrakeIndexes[6] = 3;
        BrakeIndexes[7] = 1;
    }

}

void TensionBridge::Update() {
    if (!CollidingWithPlayer) {
        for (int i = 0; i < Count; i++)
{
            Children[i]->Y = Y + i * Angled;
        }
    }

    if (Scene->ZoneID == 2) {
        int j = 0;
        if (Scene->LevelTriggerFlag >= 0x80 && !Broken) {
            Timer = 16;
            Broken = true;
        }

        if (Timer > 0 && (Timer & 1)) {
            j = BrakeIndexes[7 - (Timer >> 1)];
            Scene->AddExplosion(4, false, Children[j]->X, Children[j]->Y);
            Scene->AddMovingSprite(Sprite, Children[j]->X, Children[j]->Y, 18, 0, false, false, 0, 0, 0x38);
            Sound::Play(Sound::SFX_DESTROY);
            Children[j]->Active = false;
        }

    }

    if (Timer >= 0) Timer--;

    Object::Update();
}

void TensionBridge::Render(int CamX, int CamY) {
    for (int i = 0; i < Count; i++)
{
    }
    }

int TensionBridge::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Scene->Players[PlayerID]->Ground) return 0;

    int MaxDep = 0;
    CurSegment = (Scene->Player->EZX - (X - 8 - Count * 8)) >> 4;
    for (int i = 0; i < Count; i++)
{
        Children[i]->Rotation = false;
    }
    if (CurSegment >= 0 && CurSegment < Count) {
        Children[CurSegment]->Rotation = true;
        MaxDep = Children[CurSegment]->Timer;
    }

    for (int i = 0; i < Count; i++)
{
        if (i <= CurSegment) {
            Children[i]->Y = (Y + (MaxDep * -Math::sinHex(0x40 * (i + 1) / (CurSegment + 1)) >> 16)) + i * Angled;
        }
        else {
            Children[i]->Y = (Y + (MaxDep * -Math::sinHex(0x40 * (Count - i) / (Count - CurSegment)) >> 16)) + i * Angled;
        }
    }
    switch (Scene->ZoneID) {
        case 5:
        for (int i = 0; i < Count; i++)
{
            if (i == CurSegment) {
                Children[i]->AutoAnimate = true;
                Children[i]->Frame = 1;
            }

        }
    break;
}

return 1;
}


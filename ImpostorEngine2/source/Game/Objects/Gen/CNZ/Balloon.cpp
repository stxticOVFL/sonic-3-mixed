// Object ID: 0x41
// Object Name: Balloon.cpp

#include "Balloon.h"

typedef IMath Math;

void Balloon::Create() {
    Object::Create();
    Priority = false;
    W = 32;
    H = 32;
    VisW = 16;
    VisH = 64;
    Color = SubType & 0x7F;
    CreateBubble = (SubType & 0x80) == 0x80;
    Popped = false;
    CurrentAnimation = Sprite->FindAnimation("Default") + Color;
    MaxAccel = 0xC0;
    YSpeed = 0xC0;
    Acceleration = 0x10;
    SwingDirection = 0;
    AutoAnimate = true;
}

void Balloon::Update() {
    Swing_UpAndDown();
    Object::Update();
}

void Balloon::OnAnimationFinish() {
    if (Popped) {
        Active = false;
    }

}

int Balloon::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Popped) return false;

    Scene->Players[PlayerID]->YSpeed = -0x700;
    if (Scene->Players[PlayerID]->Underwater) Scene->Players[PlayerID]->YSpeed >>= 1;

    Scene->Players[PlayerID]->Ground = false;
    Scene->Players[PlayerID]->JumpVariable = 0;
    Sound::Play(Sound::SFX_BALLOON_POP);
    if (CreateBubble && Y > Scene->WaterLevel) {
        Object* Bubble = Scene->AddNewObject(Obj_BubbleAir, 0, X, Y, false, false);
        Bubble->CurrentAnimation = 3;
    }

    Popped = true;
    CurrentAnimation += 5;
    AnimationFrame = -2;
    Frame = 0;
    return true;
}


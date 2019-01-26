// Object ID: 0xFFFFFFFF
// Object Name: Signpost.cpp

#include "Signpost.h"

typedef IMath Math;

void Signpost::Create() {
    Object::Create();
    W = 48;
    H = 24;
    Active = true;
    Priority = true;
    CurrentAnimation = int(Scene->Players[0]->Character);
    SubX = X << 16;
    SubY = Y << 16;
    XSpeed = 0;
    YSpeed = 0;
    Frame = 0x00;
    SpinSpeed = 0x600;
    Rot = 0;
    Falling = true;
    Timer = -1;
}

void Signpost::Update() {
    if (Falling) YSpeed += 0xC;
    else Scene->Player->UnderwaterTimer = 1800;
    SubX += XSpeed << 8;
    SubY += YSpeed << 8;
    X = SubX >> 16;
    Y = SubY >> 16;
    for (int i = 0; i <= 8; i++)
{
        if (Scene->CollisionAt(SubX >> 16, Y + 24) || Y + 24 >= Scene->CameraY + App->HEIGHT) {
            if (Falling) {
                Falling = false;
                Timer = 0x48;
            }

            YSpeed = 0;
            SubY -= 0x10000;
            SubY &= 0xFFFF0000;
            Y = SubY >> 16;
        }

    }
    Rot += SpinSpeed;
    if (Timer > 0) {
        Timer--;
    }

    if (Timer == 0 && (Rot >> 8 & 0xFF) == 0x80) {
        SpinSpeed = 0;
        App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);
        Scene->ShowResults = true;
        Scene->ResultsTimer = 0;
        if (Scene->Timer < 60 * 60) Scene->TimerTotal = 50000;
        else if (Scene->Timer < 90 * 60) Scene->TimerTotal = 10000;
        else if (Scene->Timer < 120 * 60) Scene->TimerTotal = 5000;
        else if (Scene->Timer < 150 * 60) Scene->TimerTotal = 4000;
        else if (Scene->Timer < 180 * 60) Scene->TimerTotal = 3000;
        else if (Scene->Timer < 210 * 60) Scene->TimerTotal = 1000;
        else if (Scene->Timer < 599 * 60) Scene->TimerTotal = 100;
        else Scene->TimerTotal = 100000;
        Scene->TotalToAdd = 0;
        Scene->Player->DoVictory();
        App->Audio->ClearMusic();
        App->Audio->PushMusic(Sound::SoundBank[0xFC], false, 0);
        Timer = -1;
    }

    Object::Update();
}

void Signpost::Render(int CamX, int CamY) {
    int c = 0;
    int s = 0;
    int x = 0;
    int w = 0;
    Sprite = Scene->Objects2Sprite;
    G->DrawSprite(Sprite, 6, 2, X - CamX, Y - CamY, 0, IE_NOFLIP);
    c = Math::cosHex(Rot >> 8);
    s = Math::sinHex(Rot >> 8);
    x = (24 * c >> 16) + (-4 * s >> 16);
    w = (24 * c >> 16) + (4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, 6, 1, X - CamX + x + 4, Y - CamY + 22 + Sprite->Animations[6].Frames[1].OffY, 0, IE_NOFLIP, w - x, 30);

    x = (-24 * c >> 16) + (4 * s >> 16);
    w = (-24 * c >> 16) + (-4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, 6, 1, X - CamX + x + 4, Y - CamY + 22 + Sprite->Animations[6].Frames[1].OffY, 0, IE_NOFLIP, w - x, 30);

    x = (24 * c >> 16) + (4 * s >> 16);
    w = (-24 * c >> 16) + (4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, CurrentAnimation, Frame >> 8, X - CamX + x + 24, Y - CamY + 22 + Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].OffY, 0, IE_NOFLIP, w - x, 30);

    x = (-24 * c >> 16) + (-4 * s >> 16);
    w = (24 * c >> 16) + (-4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, 5, Frame >> 8, X - CamX + x + 24, Y - CamY + 22 + Sprite->Animations[5].Frames[Frame >> 8].OffY, 0, IE_NOFLIP, w - x, 30);

    }

int Signpost::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    return 0;
    if (Scene->Players[PlayerID]->Action != ActionType::Jumping) return 0;

    if (Scene->Players[PlayerID]->YSpeed > 0) return 0;

    if (YSpeed < 0) return 0;

    if (Falling) YSpeed = -0x200;

    SpinSpeed = 0xC00;
    return 1;
}


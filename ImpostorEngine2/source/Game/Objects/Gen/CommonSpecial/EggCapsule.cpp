// Object ID: 0x81
// Object Name: EggCapsule.cpp

#include "EggCapsule.h"

typedef IMath Math;

void EggCapsule::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    Flying = FlipY;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 64;
    CurrentAnimation = 16;
    Broken = false;
    if (Flying) {
        MaxAccel = 0xC0;
        YSpeed = 0xC0;
        Acceleration = 0x10;
        SwingDirection = 0;
    }
    else {
        Gravity = 0x70;
    }
    Button = Scene->AddNewObject(Obj_EggCapsuleButton, 0, X, Y - 32, false, FlipY);
    Button->Sprite = Sprite;
    Button->CurrentAnimation = CurrentAnimation + 1;
    VisualLayer = 1;
}

void EggCapsule::Update() {
    if (Flying) {
        Swing_UpAndDown();
    }
    else {
        if (Gravity) {
            while (Scene->CollisionAt(X, Y + 32 + 1)) {
                Y--;
                YSpeed = 0;
                Gravity = 0;
            }

            if (Gravity == 0) {
                Y++;
                Y++;
                Sound::Play(Sound::SFX_IMPACT4);
                Scene->ShakeTimer = 20;
            }

        }

    }
    Button->SubY = SubY + (YSpeed << 8) - 0x200000;
    Button->InitialY = Button->SubY >> 16;
    if (Button->BounceOffShield && !Broken) {
        Broken = true;
        Scene->StopTimer = true;
        Sound::Play(Sound::SFX_DESTROY);
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
    }

    Object::Update();
}

void EggCapsule::Render(int CamX, int CamY) {
    if (Flying) {
        G->DrawSprite(Sprite, CurrentAnimation + 3, Scene->Frame & 3, X - 20 - CamX, Y - 36 - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation + 3, Scene->Frame & 3, X + 20 - CamX, Y - 36 - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, Broken, X - CamX, Y - CamY, 0, IE_FLIPY);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, Broken, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }
    }


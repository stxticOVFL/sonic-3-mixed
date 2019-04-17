// Object ID: 0x81
// Object Name: EggCapsule.cpp

#include "EggCapsule.h"

typedef IMath Math;

void EggCapsule::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    Flying = FlipY;
    Sprite = LevelScene::LoadSpriteFromBin("Global/EggPrison.bin", SaveGame::CurrentMode);
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 64;
    CurrentAnimation = Sprite->FindAnimation("Capsule");
    TimerX = 0;
    TimerY = 0;
    Left = false;
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
    if (!Flying) Button = Scene->AddNewObject(Obj_EggCapsuleButton, 0, X, Y - 32, false, FlipY);
    else Button = Scene->AddNewObject(Obj_EggCapsuleButton, 0, X, Y + 32, false, FlipY);
    Button->VisualLayer = VisualLayer;
    Button->Sprite = Sprite;
    Button->CurrentAnimation = CurrentAnimation + 1;
    Button->Parent = this;
    VisualLayer = 1;
    Button->VisualLayer = VisualLayer;
}

void EggCapsule::Update() {
    if (!isHeldDebugObject) {
        if (Flying) {
            Swing_UpAndDown();
            if (Y < Scene->CameraY + (H / 2)) {
                TimerY++;
                if (TimerY >= 3) {
                    Y++;
                    TimerY = 0;
                }

            }

            TimerX++;
            if (TimerX >= 2) {
                if (!Left) X++;

                if (Left) X--;

                TimerX = 0;
            }

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
        Button->InitialY = FlipY ? Y + (H / 2) : Y - (H / 2);
        Button->X = X;
        if (Button->BounceOffShield && !Broken) {
            Broken = true;
            Scene->StopTimer = true;
            Sound::Play(Sound::SFX_DESTROY);
			App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);
            Scene->DoResults();
        }

    }

    if (X + (W / 2) >= Scene->CameraX + App->WIDTH) {
        Left = true;
    }
    else {
        if (X - (W / 2) <= Scene->CameraX) {
            Left = false;
        }

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
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

void EggCapsule::OnDestroy() {
    if (isHeldDebugObject) {
        Button->OnDestroy();
        Button->Active = false;
        Button->Visible = false;
    }

}


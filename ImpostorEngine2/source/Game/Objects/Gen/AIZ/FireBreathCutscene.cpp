// Object ID: 0x90
// Object Name: FireBreathCutscene.cpp

#include "FireBreathCutscene.h"

typedef IMath Math;

CONSTRUCTER FireBreathCutscene::FireBreathCutscene() {
}

void FireBreathCutscene::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 48;
    H = 48;
    Radius = 24;
    CurrentAnimation = 7;
    Frame = 0;
    XSpeed = 0;
    YSpeed = 0;
    VisualLayer = 1;
    MaxAccel = 0;
    Acceleration = 0;
    SwingDirection = 0;
    HitCount = 0xFF;
    Boss = true;
    TimerAction = -1;
    Timer = 0;
    InvulnTimer = 0;
    ExplosionTimer = 0x80;
    State = 2;
    OpenHatch = false;
    OpenHatchTimer = 0;
    Shot1 = -1;
    Shot2 = -1;
    Shot3 = -1;
    Cutscene = ID == Obj_FireBreathCutscene;
    int i = 0;
    MainPalette[i++] = 0x000000;
    MainPalette[i++] = 0xEEEEEE;
    MainPalette[i++] = 0x8888EE;
    MainPalette[i++] = 0x6666CC;
    MainPalette[i++] = 0x4466AA;
    MainPalette[i++] = 0xEEEE00;
    MainPalette[i++] = 0x888800;
    MainPalette[i++] = 0x224466;
    MainPalette[i++] = 0x002200;
    MainPalette[i++] = 0x000000;
    MainPalette[i++] = 0x004422;
    MainPalette[i++] = 0x002200;
    MainPalette[i++] = 0xCCCCEE;
    MainPalette[i++] = 0x8888AA;
    MainPalette[i++] = 0x444466;
    MainPalette[i++] = 0x444400;
    i = 0;
    HurtPalette[i++] = 0x000000;
    HurtPalette[i++] = 0xEEEEEE;
    HurtPalette[i++] = 0x8888EE;
    HurtPalette[i++] = 0x6666CC;
    HurtPalette[i++] = 0x4466AA;
    HurtPalette[i++] = 0xEEEE00;
    HurtPalette[i++] = 0x888800;
    HurtPalette[i++] = 0x888888;
    HurtPalette[i++] = 0x002200;
    HurtPalette[i++] = 0x000000;
    HurtPalette[i++] = 0xAAAAAA;
    HurtPalette[i++] = 0xEEEEEE;
    HurtPalette[i++] = 0xCCCCEE;
    HurtPalette[i++] = 0x8888AA;
    HurtPalette[i++] = 0xAAAAAA;
    HurtPalette[i++] = 0x444400;
    Sprite->SetPalette(0x10, 16, MainPalette);
    Sprite->UpdatePalette();
    if (Cutscene) {
        Scene->AddNewObject(Obj_TreeBark, 0, 0x2F78, 0x318, false, false);
        SmallX = 0;
        SmallerX = 0;
        SmallestX = 0;
        X = 0x2F10 + App->WIDTH - 0x30;
        VisualLayer = 0;
    }
    else {
        HitCount = 6;
        Boss = true;
        State = 2;
    }
}

int FireBreathCutscene::OnHit() {
    HitCount--;
    if (HitCount == 0) {
        Scene->StopTimer = true;
        Scene->Score += 1000;
        HitCount = -1;
        return 0;
    }

    InvulnTimer = 0x20;
    return 0;
}

void FireBreathCutscene::DoExplosionDebris() {
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 0, FlipX, false, -0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 1, FlipX, false, 0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 2, FlipX, false, -0x400, -0x400, 0x48);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 3, FlipX, false, 0x400, -0x400, 0x48);
    Object* Signpost = Scene->AddNewObject(Obj_Signpost, 0x00, X, Scene->CameraY - 64, false, false);
    Signpost->VisualLayer = VisualLayer;
}

void FireBreathCutscene::HandleDamage() {
    if (HitCount > 0) {
        if (InvulnTimer > 0) {
            InvulnTimer -= 1;
            Invincible = true;
            Harmful = false;
        }
        else {
            Invincible = false;
            Harmful = true;
        }
    }

    if (InvulnTimer > 0) {
        if (InvulnTimer & 1) {
            Sprite->SetPalette(0x10, 16, MainPalette);
            Sprite->UpdatePalette();
        }
        else {
            Sprite->SetPalette(0x10, 16, HurtPalette);
            Sprite->UpdatePalette();
        }
    }

    if (HitCount < 0) {
        VisualLayer = 1;
        if (ExplosionTimer > 0) {
            if (ExplosionTimer % 3 == 0) {
                Scene->AddExplosion(5, false, X + Math::randRange(-W / 2, W / 2), Y + Math::randRange(-H / 2, H / 2), VisualLayer);
                Sound::Play(Sound::SFX_BOSSEXPLOSION);
            }

            ExplosionTimer--;
        }
        else {
            DoExplosionDebris();
            Active = false;
            App->Audio->FadeMusic(3.0);
        }
        XSpeed = 0;
        YSpeed = 0;
    }

}

void FireBreathCutscene::Update() {
    if (!isHeldDebugObject) {
        switch (State) {
            case 2:
            if (Cutscene) {
                if (Scene->CameraX >= 0x2F10) {
                    TimerAction = 0;
                    State = 4;
                    Timer = 0xB4;
                    App->Audio->FadeMusic(3.0);
                }

            }
            else {
                if (Scene->CameraX >= 0x10E0 + 160 - App->WIDTH / 2) {
                    TimerAction = 0;
                    State = 4;
                    Timer = 0xB4;
                    App->Audio->FadeMusic(3.0);
                }

            }
            break;
            case 4:
            break;
            case 6:
            break;
            case 8:
            Swing_UpAndDown();
            break;
        }

        if (Timer > 0) Timer--;
        else if (Timer == 0) {
            Timer = -1;
            switch (TimerAction) {
                case 0:
                TimerAction = 1;
                State = 6;
                YSpeed = 0x100;
                Timer = 0xAF;
                SmallerX = 0x2F0000 - (132 + 120) * 0x180;
                SmallestX = 0x2F0000 - 120;
                App->Audio->PushMusic(Sound::SoundBank[0xF1], true, 0);
                break;
                case 1:
                SmallX = 0x2F0000 - 240 * 0x200;
                Timer = 0x7F;
                TimerAction = 2;
                SwingDirection = 1;
                State = 8;
                YSpeed = 0x00;
                MaxAccel = 0xC0;
                YSpeed = 0xC0;
                Acceleration = 0x10;
                SwingDirection = 0;
                OpenHatch = true;
                break;
                case 2:
                Timer = 0x10;
                TimerAction = 3;
                break;
                case 3:
                if (!Cutscene) break;

                XSpeed = 0x400;
                YSpeed = 0x0;
                State = -1;
                App->Audio->FadeMusic(3.0);
                App->Audio->RemoveMusic(Sound::SoundBank[0]);
                Timer = 0x120;
                TimerAction = 4;
                Scene->LevelTriggerFlag = 0x80;
                break;
                case 4:
                App->Audio->PushMusic(Sound::SoundBank[0], true, 0);
                break;
            }

        }

        HandleDamage();
        MoveSprite();
        if (Cutscene) {
        }

        if (OpenHatch) {
            if (OpenHatchTimer < 0x2F) {
                OpenHatchTimer++;
            }
            else if (OpenHatchTimer == 0x2F) {
                Shot1 = 0;
                Shot2 = 12;
                Shot3 = 6;
                OpenHatchTimer++;
            }

        }

        if (Shot1 >= 0) Shot1 = (Shot1 + 1) & 0x1F;

        if (Shot2 >= 0) Shot2 = (Shot2 + 1) & 0x1F;

        if (Shot3 >= 0) Shot3 = (Shot3 + 1) & 0x1F;

        if (State < 4 && State >= 0) return;

        SmallX += 0x200;
        SmallerX += 0x180;
        SmallestX += 0x100;
    }

    return;
    Object::Update();
}

void FireBreathCutscene::Render(int CamX, int CamY) {
    if (Cutscene) {
        G->DrawSprite(Sprite, CurrentAnimation + 2, 2, (SmallestX >> 8) - CamX, 0x328 - CamY, 0, FlipX);
        G->DrawSprite(Sprite, CurrentAnimation + 2, 2, (SmallestX >> 8) - 72 - CamX, 0x328 - CamY, 0, FlipX);
        G->DrawSprite(Sprite, CurrentAnimation + 2, 1, (SmallerX >> 8) - CamX, 0x31C - CamY, 0, FlipX);
        G->DrawSprite(Sprite, CurrentAnimation + 2, 1, (SmallerX >> 8) - 72 - CamX, 0x31C - CamY, 0, FlipX);
        G->DrawSprite(Sprite, CurrentAnimation + 2, 0, (SmallX >> 8) - CamX, 0x30C - CamY, 0, FlipX);
        G->DrawSprite(Sprite, CurrentAnimation + 2, 0, (SmallX >> 8) - 72 - CamX, 0x30C - CamY, 0, FlipX);
    }

    int OHT;
    OHT = OpenHatchTimer;
    if (OHT > 0xF) OHT = 0xF;

    G->DrawSprite(Sprite, CurrentAnimation, 3 + (OHT / 6), X - CamX, Y - 32 - CamY, 0, FlipX);
    OHT = OpenHatchTimer - 0x10;
    if (OHT < 0) OHT = 0;

    if (OHT > 0xF) OHT = 0xF;

    G->DrawSprite(Sprite, CurrentAnimation, 3 + (OHT / 6), X + 9 - CamX, Y - 28 - CamY, 0, FlipX);
    OHT = OpenHatchTimer - 0x20;
    if (OHT < 0) OHT = 0;

    if (OHT > 0xF) OHT = 0xF;

    G->DrawSprite(Sprite, CurrentAnimation, 3 + (OHT / 6), X + 18 - CamX, Y - 24 - CamY, 0, FlipX);
    if (Shot1 >= 0 && (Shot1 >> 2) < 5) G->DrawSprite(Sprite, CurrentAnimation, 7 + (Shot1 >> 2), X - CamX, Y + 4 - 32 - CamY, 0, FlipX);

    if (Shot2 >= 0 && (Shot2 >> 2) < 5) G->DrawSprite(Sprite, CurrentAnimation, 7 + (Shot2 >> 2), X + 9 - CamX, Y + 4 - 28 - CamY, 0, FlipX);

    if (Shot3 >= 0 && (Shot3 >> 2) < 5) G->DrawSprite(Sprite, CurrentAnimation, 7 + (Shot3 >> 2), X + 18 - CamX, Y + 4 - 24 - CamY, 0, FlipX);

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX);
    G->DrawSprite(Sprite, CurrentAnimation, 1 + (Scene->Frame >> 1 & 1), X - CamX, Y - CamY, 0, FlipX);
    G->DrawSprite(Sprite, CurrentAnimation, 6, X - CamX, Y - CamY, 0, FlipX);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


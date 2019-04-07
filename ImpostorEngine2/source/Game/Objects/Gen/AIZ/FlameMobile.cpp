// Object ID: 0x92
// Object Name: FlameMobile.cpp

#include "FlameMobile.h"

typedef IMath Math;

CONSTRUCTER FlameMobile::FlameMobile() {
}

void FlameMobile::Create() {
    Enemy::Create();
    Visible = true;
    Active = true;
    Priority = true;
    W = 48;
    H = 96;
    HitboxEnemy.Top = -64;
    HitboxEnemy.Left = -24;
    HitboxEnemy.Right = 24;
    HitboxEnemy.Bottom = 24;
    CurrentAnimation = 5;
    Frame = 0;
    XSpeed = 0;
    YSpeed = 0;
    VisualLayer = 0;
    MaxAccel = 0;
    Acceleration = 0;
    SwingDirection = 0;
    HitCount = 8;
    Boss = true;
    TimerAction = -1;
    Timer = 0;
    InvulnTimer = 0;
    ExplosionTimer = 0x80;
    State = BossState::WAITING_FOR_PLAYER;
    ArmBackAngle = 0;
    ArmFrontAngle = 0;
    BehindWaterFall = true;
    EmergeFromWaterTimer = -1;
    DryTimer = -1;
    TargetX = X;
    TargetY = Y;
    TargetIndex = 0;
    int i = 0;
    MainPalette[i++] = 0x000000;
    MainPalette[i++] = 0xEEEEEE;
    MainPalette[i++] = 0xAAAACC;
    MainPalette[i++] = 0x6622EE;
    MainPalette[i++] = 0x222222;
    MainPalette[i++] = 0xEEEE00;
    MainPalette[i++] = 0x888800;
    MainPalette[i++] = 0x880000;
    MainPalette[i++] = 0xEEAA22;
    MainPalette[i++] = 0xCC4400;
    MainPalette[i++] = 0x660000;
    MainPalette[i++] = 0x002200;
    MainPalette[i++] = 0x8866CC;
    MainPalette[i++] = 0x4422AA;
    MainPalette[i++] = 0x222266;
    MainPalette[i++] = 0x444400;
    i = 0;
    HurtPalette[i++] = 0x000000;
    HurtPalette[i++] = 0xEEEEEE;
    HurtPalette[i++] = 0xAAAACC;
    HurtPalette[i++] = 0x6622EE;
    HurtPalette[i++] = 0xAAAAAA;
    HurtPalette[i++] = 0xEEEE00;
    HurtPalette[i++] = 0x888800;
    HurtPalette[i++] = 0xAAAAAA;
    HurtPalette[i++] = 0xEEAA22;
    HurtPalette[i++] = 0xAAAAAA;
    HurtPalette[i++] = 0xCCCCCC;
    HurtPalette[i++] = 0xEEEEEE;
    HurtPalette[i++] = 0x8866CC;
    HurtPalette[i++] = 0x666666;
    HurtPalette[i++] = 0x888888;
    HurtPalette[i++] = 0x444400;
    AniWaterSplashing[0x0] = 0x2B;
    AniWaterSplashing[0x1] = 0x2B;
    AniWaterSplashing[0x2] = 0x2B;
    AniWaterSplashing[0x3] = 0;
    AniWaterSplashing[0x4] = 0x2B;
    AniWaterSplashing[0x5] = 0x2B;
    AniWaterSplashing[0x6] = 0;
    AniWaterSplashing[0x7] = 0x2B;
    AniWaterSplashing[0x8] = 0x2B;
    AniWaterSplashing[0x9] = 0;
    AniWaterSplashing[0xA] = 0x2B;
    AniWaterSplashing[0xB] = 0x2B;
    AniWaterSplashing[0xC] = 0;
    if (Y > 0x200) Active = false;

}

int FlameMobile::OnHit() {
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

void FlameMobile::DoExplosionDebris() {
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 0, FlipX, false, -0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 1, FlipX, false, 0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 2, FlipX, false, -0x400, -0x400, 0x48);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 3, FlipX, false, 0x400, -0x400, 0x48);
    if (X < 0x4948) X = 0x4948;

    Object* Signpost = Scene->AddNewObject(Obj_Signpost, 0x00, X, Scene->CameraY - 64, false, false);
    Signpost->VisualLayer = VisualLayer;
}

void FlameMobile::HandleDamage() {
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

void FlameMobile::GetTargetPos() {
    int i;
    do i = Math::randRange(0, 3);

while (TargetIndex == i);
    TargetIndex = i;
    switch (i) {
        case 0:
        TargetX = 0x58;
        TargetY = 0x76;
        break;
        case 1:
        TargetX = 0xA0;
        TargetY = 0x46;
        break;
        case 2:
        TargetX = 0x160;
        TargetY = 0x46;
        break;
        case 3:
        TargetX = 0x1A8;
        TargetY = 0x76;
        break;
    }

    if (true) {
        TargetX += 0x48E0;
        TargetY += 0x015A;
    }
    else {
        TargetX += 0x4160;
        TargetY += 0x05DA;
    }
}

void FlameMobile::Update() {
    if (!isHeldDebugObject) {
        switch (State) {
            case BossState::WAITING_FOR_PLAYER:
            VisualLayer = 0;
            Visible = false;
            if (Scene->CameraX >= 0x4880) {
                TimerAction = BossAction::START_FIGHT;
                Timer = 0xB4;
                App->Audio->FadeMusic(3.0);
                State = BossState::WAIT_NO_MOVE;
                Scene->CameraMinX = 0x4880;
                Scene->CameraMaxX = 0x4880;
                Scene->CameraX = 0x4880;
                Sprite->SetPalette(0x10, 16, MainPalette);
                Sprite->UpdatePalette();
            }

            break;
            case BossState::EMERGE_FROM_WATER:
            VisualLayer = 1;
            if (EmergeFromWaterTimer > 0) EmergeFromWaterTimer--;
            else if (!EmergeFromWaterTimer) {
                EmergeFromWaterTimer = -1;
                State = BossState::WATER_DRY;
                BehindWaterFall = false;
                DryTimer = 5 + 6 + 7;
                break;
            }

            BehindWaterFall = !!AniWaterSplashing[12 - EmergeFromWaterTimer];
            break;
            case BossState::WATER_DRY:
            if (DryTimer > 0) DryTimer--;
            else if (!DryTimer) {
                DryTimer = -1;
                State = BossState::WAIT;
                Timer = 0x1F;
                TimerAction = BossAction::SOMEKINDAWAIT;
                MaxAccel = 0xC0;
                YSpeed = 0xC0;
                Acceleration = 0x10;
                break;
            }

            break;
            case BossState::WAIT:
            Swing_UpAndDown();
            break;
            case BossState::WAIT_NO_MOVE:
            if (VisualLayer == 0) FlipX = Scene->Player->EZX < X;

            break;
            case BossState::SHIFT_CAMERA:
            if (Scene->CameraMinX < 0x48E0) {
                Scene->CameraMinX += 2;
                Scene->CameraMaxX = Scene->CameraMinX;
            }
            else Scene->CameraMaxX = 0x4B00 - App->WIDTH;
            if (Scene->CameraX < Scene->CameraMinX) Scene->CameraX = Scene->CameraMinX;

            if (VisualLayer == 0) FlipX = Scene->Player->EZX < X;

            break;
        }

        if (Timer > 0) Timer--;
        else if (Timer == 0) {
            Timer = -1;
            switch (TimerAction) {
                case BossAction::START_FIGHT:
                Visible = true;
                State = BossState::EMERGE_FROM_WATER;
                EmergeFromWaterTimer = 12;
                Sound::Play(Sound::SFX_SPLASH);
                App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
                App->Audio->PushMusic(Sound::SoundBank[0xF0], true, 0);
                break;
                case BossAction::SOMEKINDAWAIT:
                Timer = 0x2F;
                TimerAction = BossAction::WAIT_LONG;
                if (false) {
                    if (false) Timer = 0xBF;
                    else Timer = 0xFF;
                    TimerAction = BossAction::WAIT_SHORT;
                }

                break;
                case BossAction::WAIT_LONG:
                Scene->Signal[0] = 1;
                Timer = 0x8F;
                TimerAction = BossAction::WAIT_SHORT;
                break;
                case BossAction::WAIT_SHORT:
                State = BossState::WAIT_NO_MOVE;
                Timer = 0x3F;
                TimerAction = BossAction::HIDE_BEHIND;
                XSpeed = 0;
                YSpeed = 0;
                break;
                case BossAction::HIDE_BEHIND:
                VisualLayer = 0;
                BehindWaterFall = true;
                State = BossState::WAIT_NO_MOVE;
                Sound::Play(Sound::SFX_SPLASH);
                Timer = 1;
                TimerAction = BossAction::START_MOVING;
                break;
                case BossAction::START_MOVING:
                State = BossState::SHIFT_CAMERA;
                if (Scene->CameraMinX >= 0x48E0) State = BossState::WAIT_NO_MOVE;

                GetTargetPos();
                XSpeed = (TargetX - X) << 1;
                YSpeed = (TargetY - Y) << 1;
                Timer = 0x7F;
                TimerAction = BossAction::STOP_AND_EMERGE;
                break;
                case BossAction::STOP_AND_EMERGE:
                XSpeed = 0;
                YSpeed = 0;
                State = BossState::EMERGE_FROM_WATER;
                EmergeFromWaterTimer = 12;
                Sound::Play(Sound::SFX_SPLASH);
                break;
            }

        }

        HandleDamage();
        if (BehindWaterFall) {
            Invincible = true;
            Harmful = false;
        }

        if (HitCount > 0) {
            if (Math::abs(Scene->Player->X - X) < 32) {
                ArmBackAngle = 2;
                ArmFrontAngle = 2;
            }
            else {
                ArmBackAngle = 1;
                ArmFrontAngle = 1;
            }
        }

    }

    Object::Update();
}

void FlameMobile::Render(int CamX, int CamY) {
    if (!Visible) return;

    bool ShowMainBody = true;
    int Flip = 1;
    if (FlipX) Flip = -1;

    if (EmergeFromWaterTimer >= 0) {
        if (AniWaterSplashing[12 - EmergeFromWaterTimer]) ShowMainBody = false;

    }

    if (ShowMainBody) {
        int offX = 40;
        G->DrawSprite(Sprite, CurrentAnimation, 1, X + (offX - 20) * Flip - CamX, Y - 4 - CamY, 0, !FlipX);
        switch (ArmBackAngle) {
            case 0:
            {
                G->DrawSprite(Sprite, CurrentAnimation, 4, X + (offX + 8) * Flip - CamX, Y - 4 - CamY, 0, !FlipX);
                break;
            }
            case 1:
            {
                G->DrawSprite(Sprite, CurrentAnimation, 5, X + (offX + 4) * Flip - CamX, Y + 4 - CamY, 0, !FlipX);
                G->DrawSprite(Sprite, CurrentAnimation, 10, X + (offX + 8) * Flip - CamX, Y + 9 - CamY, 0, !FlipX);
                break;
            }
            case 2:
            {
                G->DrawSprite(Sprite, CurrentAnimation, 6, X + (offX - 3) * Flip - CamX, Y + 12 - CamY, 0, !FlipX);
                G->DrawSprite(Sprite, CurrentAnimation, 14, X + (offX - 3) * Flip - CamX, Y + 19 - CamY, 0, !FlipX);
                break;
            }
        }

        if (InvulnTimer > 0) G->DrawSprite(Scene->RobotnikSprite, 2, 0, X - CamX, Y - 48 - CamY, 0, !FlipX);
        else if (HitCount < 0) G->DrawSprite(Scene->RobotnikSprite, 3, 0, X - CamX, Y - 48 - CamY, 0, !FlipX);
        else G->DrawSprite(Scene->RobotnikSprite, 0, (Scene->Frame / 6) & 1, X - CamX, Y - 48 - CamY, 0, !FlipX);
        G->DrawSprite(Scene->RobotnikSprite, 8, 0, X - CamX, Y - 20 - CamY, 0, !FlipX);
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, FlipX);
        offX = 0;
        G->DrawSprite(Sprite, CurrentAnimation, 1, X - 20 * Flip - CamX, Y - 4 - CamY, 0, !FlipX);
        switch (ArmFrontAngle) {
            case 0:
            {
                G->DrawSprite(Sprite, CurrentAnimation, 4, X + (offX + 8) * Flip - CamX, Y - 4 - CamY, 0, !FlipX);
                break;
            }
            case 1:
            {
                G->DrawSprite(Sprite, CurrentAnimation, 5, X + (offX + 4) * Flip - CamX, Y + 4 - CamY, 0, !FlipX);
                G->DrawSprite(Sprite, CurrentAnimation, 10, X + (offX + 8) * Flip - CamX, Y + 9 - CamY, 0, !FlipX);
                break;
            }
            case 2:
            {
                G->DrawSprite(Sprite, CurrentAnimation, 6, X + (offX - 3) * Flip - CamX, Y + 12 - CamY, 0, !FlipX);
                G->DrawSprite(Sprite, CurrentAnimation, 14, X + (offX - 3) * Flip - CamX, Y + 19 - CamY, 0, !FlipX);
                break;
            }
        }

    }

    if (EmergeFromWaterTimer >= 0) {
        if (!ShowMainBody) G->DrawSprite(Sprite, CurrentAnimation, 0x2B, X - CamX, Y - CamY, 0, EmergeFromWaterTimer & 1);

    }

    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }


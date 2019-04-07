// Object ID: 0x99
// Object Name: BigShaker.cpp

#include "BigShaker.h"

typedef IMath Math;

CONSTRUCTER BigShaker::BigShaker() {
}

void BigShaker::Create() {
    Enemy::Create();
    TimerSpin = 0;
    SpinSpeed = 0;
    RocketSpeed = 0;
    RocketTurn = 0;
    InvulnTimer = 0;
    Started = false;
    ExplosionTimer = 0x80;
    Active = true;
    Priority = false;
    IdlePosY = InitialY + 0xEB;
    PillarX = InitialX;
    PillarY = InitialY + 352;
    VisualLayer++;
    W = 64;
    H = 64;
    Radius = 32;
    Y += 0x30;
    Timer = 0;
    HitCount = 6;
    Boss = true;
    CurrentAnimation = Sprite->FindAnimation("Main");
    PlayerEntered = false;
    State = BossState::ENTERING;
    int i = 0;
    MainPalette[i++] = Sprite->Palette[0x10];
    MainPalette[i++] = Sprite->Palette[0x11];
    MainPalette[i++] = Sprite->Palette[0x12];
    MainPalette[i++] = Sprite->Palette[0x13];
    MainPalette[i++] = Sprite->Palette[0x14];
    MainPalette[i++] = Sprite->Palette[0x15];
    MainPalette[i++] = Sprite->Palette[0x16];
    MainPalette[i++] = Sprite->Palette[0x17];
    MainPalette[i++] = Sprite->Palette[0x18];
    MainPalette[i++] = Sprite->Palette[0x19];
    MainPalette[i++] = Sprite->Palette[0x1A];
    MainPalette[i++] = Sprite->Palette[0x1B];
    MainPalette[i++] = Sprite->Palette[0x1C];
    MainPalette[i++] = Sprite->Palette[0x1D];
    MainPalette[i++] = Sprite->Palette[0x1E];
    MainPalette[i++] = Sprite->Palette[0x1F];
    i = 0;
    MainPalette[i++] = Sprite->PaletteAlt[0x10];
    MainPalette[i++] = Sprite->PaletteAlt[0x11];
    MainPalette[i++] = Sprite->PaletteAlt[0x12];
    MainPalette[i++] = Sprite->PaletteAlt[0x13];
    MainPalette[i++] = Sprite->PaletteAlt[0x14];
    MainPalette[i++] = Sprite->PaletteAlt[0x15];
    MainPalette[i++] = Sprite->PaletteAlt[0x16];
    MainPalette[i++] = Sprite->PaletteAlt[0x17];
    MainPalette[i++] = Sprite->PaletteAlt[0x18];
    MainPalette[i++] = Sprite->PaletteAlt[0x19];
    MainPalette[i++] = Sprite->PaletteAlt[0x1A];
    MainPalette[i++] = Sprite->PaletteAlt[0x1B];
    MainPalette[i++] = Sprite->PaletteAlt[0x1C];
    MainPalette[i++] = Sprite->PaletteAlt[0x1D];
    MainPalette[i++] = Sprite->PaletteAlt[0x1E];
    MainPalette[i++] = Sprite->PaletteAlt[0x1F];
    i = 0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0x800000;
    HurtPalette[i++] = 0xb03000;
    HurtPalette[i++] = 0xe07000;
    HurtPalette[i++] = 0xe0a000;
    HurtPalette[i++] = 0xe0c000;
    HurtPalette[i++] = 0x200008;
    HurtPalette[i++] = 0x700010;
    HurtPalette[i++] = 0xe00020;
    HurtPalette[i++] = 0xe84848;
    HurtPalette[i++] = 0xe87878;
    HurtPalette[i++] = 0xe89898;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
}

void BigShaker::DoExplosionDebris() {
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 0, FlipX, false, -0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 1, FlipX, false, 0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 2, FlipX, false, -0x400, -0x400, 0x48);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 3, FlipX, false, 0x400, -0x400, 0x48);
    Object* Signpost = Scene->AddNewObject(Obj_Signpost, 0x00, X, Scene->CameraY - 64, false, false);
    Signpost->VisualLayer = VisualLayer;
}

int BigShaker::OnHit() {
    InvulnTimer = 0x20;
    HitCount -= 1;
    if (HitCount == 0) {
        Sprite->SetPalette(0x10, 16, MainPalette);
        Scene->StopTimer = true;
        Scene->Score += 1000;
        HitCount = -1;
        return 0;
    }

    return 0;
}

void BigShaker::HandleDamage() {
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
            if (this->Y < Scene->WaterLevel) {
                Sprite->SetPalette(0x10, 16, MainPaletteWater);
            }
            else {
                Sprite->SetPalette(0x10, 16, MainPalette);
            }
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
            Active = false;
            App->Audio->FadeMusic(3.0);
        }
        XSpeed = 0;
        YSpeed = 0;
    }

}

void BigShaker::Update() {
    int bodyLeft = 67;
    int bodyTop = 1;
    if (!isHeldDebugObject) {
        if (HitCount < 0) {
            if (ExplosionTimer > 0) {
                if (ExplosionTimer % 3 == 0) {
                    Scene->AddExplosion(5, false, X + Math::randRange(-0x20, 0x20), Y + Math::randRange(-0x20, 0x20));
                    Sound::Play(Sound::SFX_BOSSEXPLOSION);
                }

                ExplosionTimer--;
            }
            else {
                DoExplosionDebris();
                Active = false;
                App->Audio->FadeMusic(2.0);
            }
            return;
        }

        switch (State) {
            case BossState::ENTERING:
            if (Scene->Player->Y > Scene->WaterLevel - 0x40) {
                PlayerEntered = true;
                for (int i = 0; i < Scene->PlayerCount; i++)
{
                    if (Scene->Players[i]) {
                        PlayerGravity[i] = Scene->Players[i]->Gravity;
                        PlayerMoveLeft[i] = false;
                        Scene->Players[i]->VisualLayer = VisualLayer;
                    }

                }
            }

            if (PlayerEntered) {
                if (Y < IdlePosY) {
                    Y += 2;
                }
                else {
                    RocketSpeed -= 0.1;
                    if (RocketSpeed <= 0) {
                        State = BossState::SPEEDING_UP;
                        ActionTimer = 0;
                    }

                }
            }

            break;
            case BossState::MOVING:
            if (ActionTimer < 0x180) {
                if (Y > IdlePosY - 120) Y--;
                else {
                    if (ActionTimer < 0x1) {
                        int wall;
                        wall = Math::randRange(0, 5);
                        LeftWall = wall <= 3 ? true : false;
                        if (LeftWall) {
                            WallStartPos = InitialX - 0x80;
                            WallStartPos += W / 2;
                        }
                        else {
                            WallStartPos = InitialX + 0x80;
                            WallStartPos -= W / 2;
                        }
                    }

                    WallSlide();
                    ActionTimer++;
                }
            }
            else {
                Y += 2;
                if (Y >= IdlePosY) {
                    State = BossState::SPEEDING_UP;
                    X = InitialX;
                    RocketSpeed = 0;
                    ActionTimer = 0;
                }

            }
            break;
            case BossState::SLOWING_DOWN:
            if (SpinSpeed > 0x0) {
                SpinSpeed -= 0x4;
            }
            else {
                State = BossState::MOVING;
                RocketSpeed = 1;
                ActionTimer = 0;
            }
            break;
            case BossState::SPINNING_WATER:
            if (ActionTimer < 0x180) {
                if (ActionTimer < 0x10) {
                    for (int i = 0; i < Scene->PlayerCount; i++)
{
                        SpinOffsets[i] = InitialX - Scene->Players[i]->X;
                        SpinOffsets[i] = Math::abs(SpinOffsets[i]);
                        SpinOffsets[i] /= 2;
                        if (SpinOffsets[i] < 4) SpinOffsets[i] = 4;

                    }
                }

                ActionTimer++;
                if (ActionTimer > 0x180 / 4) SpinWater();

            }
            else {
                for (int i = 0; i < Scene->PlayerCount; i++)
{
                    Scene->Players[i]->ControlLocked = false;
                    Scene->Players[i]->Gravity = PlayerGravity[i];
                    Scene->Players[i]->VisualLayer = VisualLayer;
                    SpinOffsets[i] = 0;
                }
                if (RocketSpeed < 2) RocketSpeed += 0.1;
                else {
                    State = BossState::SLOWING_DOWN;
                    ActionTimer = 0;
                }
            }
            break;
            case BossState::SPEEDING_UP:
            if (SpinSpeed < 0x100) {
                SpinSpeed += 0x4;
            }
            else {
                State = BossState::SPINNING_WATER;
                ActionTimer = 0;
            }
            break;
        }

        HandleDamage();
        if (!Started) {
            App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
            App->Audio->PushMusic(Sound::SoundBank[0xF1], true, 276105);
            Started = true;
        }

        TimerSpin += SpinSpeed;
        if (TimerSpin >= (Sprite->Animations[2].FrameCount * 512)) {
            TimerSpin = 0;
        }

        RocketTurn += int(RocketSpeed);
        if (RocketTurn >= 0x40) {
            RocketTurn = 0x0;
        }

    }

    Object::Update();
}

void BigShaker::DrawRocket(int Rock, int Ang, int Flip, int Side, int CamX, int CamY) {
    Rock &= 0x3F;
    int cosval = (Math::cosHex(Rock << 2) * Radius) >> 16;
    int xx = (cosval * Math::cosHex(Ang)) >> 16;
    int yy = (cosval * Math::sinHex(Ang)) >> 16;
    if (Math::sinHex(Rock << 2) * Side >= 0) {
        if (Rock >> 2 < 4) G->DrawSprite(Sprite, 6, Rock >> 2, X - CamX + xx, Y - CamY + yy, 0, Flip);

        G->DrawSprite(Sprite, 5, Rock >> 2, X - CamX + xx, Y - CamY + yy, 0, Flip);
        if (Rock >> 2 >= 4 && Rock >> 2 < 11) G->DrawSprite(Sprite, 6, Rock >> 2, X - CamX + xx, Y - CamY + yy, 0, Flip);

    }

}

void BigShaker::Render(int CamX, int CamY) {
    for (int i = 0; i < 0x41; i += 0x20)
{
        G->DrawSprite(Sprite, 1, TimerSpin >> 9, InitialX - CamX, PillarY - CamY - i, 0, IE_NOFLIP);
    }
    G->DrawSprite(Sprite, 2, TimerSpin >> 9, InitialX - CamX, PillarY - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 0, 2, InitialX - CamX, PillarY - 0x3F - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 0, 3, InitialX - CamX, PillarY - CamY, 0, IE_NOFLIP);
    if (State != BossState::MOVING) {
        RocketTurn = 0;
        DrawRocket(RocketTurn, 0xE0, IE_NOFLIP, 1, CamX, CamY);
        DrawRocket(RocketTurn, 0xE0, IE_NOFLIP, 1, CamX, CamY);
        DrawRocket(RocketTurn, 0xA0, IE_FLIPX, 1, CamX, CamY);
        DrawRocket(RocketTurn, 0xA0, IE_FLIPX, 1, CamX, CamY);
        G->DrawSprite(Sprite, 0, 1, X - CamX, Y - CamY, 0, IE_NOFLIP);
        DrawRocket(RocketTurn, 0xE0, IE_NOFLIP, -1, CamX, CamY);
        DrawRocket(RocketTurn, 0xE0, IE_NOFLIP, -1, CamX, CamY);
        DrawRocket(RocketTurn, 0xA0, IE_FLIPX, -1, CamX, CamY);
        DrawRocket(RocketTurn, 0xA0, IE_FLIPX, -1, CamX, CamY);
    }
    else {
        DrawRocket(RocketTurn + 0x00, 0xE0, IE_NOFLIP, 1, CamX, CamY);
        DrawRocket(RocketTurn + 0x20, 0xE0, IE_NOFLIP, 1, CamX, CamY);
        DrawRocket(RocketTurn + 0x10, 0xA0, IE_FLIPX, 1, CamX, CamY);
        DrawRocket(RocketTurn + 0x30, 0xA0, IE_FLIPX, 1, CamX, CamY);
        G->DrawSprite(Sprite, 0, 1, X - CamX, Y - CamY, 0, IE_NOFLIP);
        DrawRocket(RocketTurn + 0x00, 0xE0, IE_NOFLIP, -1, CamX, CamY);
        DrawRocket(RocketTurn + 0x20, 0xE0, IE_NOFLIP, -1, CamX, CamY);
        DrawRocket(RocketTurn + 0x10, 0xA0, IE_FLIPX, -1, CamX, CamY);
        DrawRocket(RocketTurn + 0x30, 0xA0, IE_FLIPX, -1, CamX, CamY);
    }
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

void BigShaker::WallSlide() {
    X = WallStartPos;
}

void BigShaker::SpinWater() {
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (Scene->Players[i]->Y > Scene->WaterLevel) {
            Scene->Players[i]->ControlLocked = true;
            Scene->Players[i]->Gravity = 0;
            Scene->Players[i]->Action = ActionType::Fan;
            int SpinLevel;
            float SpinSpeed;
            SpinSpeed = 1;
            SpinLevel = this->Y + 100;
            if (Scene->Players[i]->Y == SpinLevel) {
            }
            else if (Scene->Players[i]->Y < SpinLevel) Scene->Players[i]->Y += 2;
            else if (Scene->Players[i]->Y > SpinLevel) Scene->Players[i]->Y -= 2;

            if (PlayerMoveLeft[i]) {
                if (Scene->Players[i]->XSpeed > -0x400) Scene->Players[i]->XSpeed -= 0x20 * SpinSpeed;

            }
            else if (!PlayerMoveLeft[i]) {
                if (Scene->Players[i]->XSpeed < 0x400) Scene->Players[i]->XSpeed += 0x20 * SpinSpeed;

            }

            if (Scene->Players[i]->X > (InitialX + SpinOffsets[i]) && !PlayerMoveLeft[i]) {
                PlayerMoveLeft[i] = true;
                Scene->Players[i]->VisualLayer = VisualLayer - 1;
                if (SpinOffsets[i] < 24) SpinOffsets[i] += 4;

            }
            else if (Scene->Players[i]->X < (InitialX - SpinOffsets[i]) && PlayerMoveLeft[i]) {
                PlayerMoveLeft[i] = false;
                Scene->Players[i]->VisualLayer = VisualLayer;
                if (SpinOffsets[i] < 24) SpinOffsets[i] += 4;

            }

            if (SpinOffsets[i] > 24) SpinOffsets[i] = 24;

        }

    }
}


// Object ID: 0x99
// Object Name: HCZMiniboss.cpp

#include "HCZMiniboss.h"

typedef IMath Math;

void HCZMiniboss::Create() {
    Enemy::Create();
    TimerSpin = 0;
    SpinSpeed = 0;
    RocketTurn = 0;
    InvulnTimer = 0;
    Started = false;
    ExplosionTimer = 0x80;
    Active = true;
    Priority = false;
    W = 64;
    H = 64;
    Y = 0x680;
    Radius = 32;
    Timer = 0;
    HitCount = 6;
    Boss = true;
    int i = 0;
    MainPalette[i++] = 0x400000;
    MainPalette[i++] = 0x900000;
    MainPalette[i++] = 0xe00000;
    MainPalette[i++] = 0x800000;
    MainPalette[i++] = 0xb03000;
    MainPalette[i++] = 0xe07000;
    MainPalette[i++] = 0xe0a000;
    MainPalette[i++] = 0xe0c000;
    MainPalette[i++] = 0x200008;
    MainPalette[i++] = 0x700010;
    MainPalette[i++] = 0xe00020;
    MainPalette[i++] = 0xe84848;
    MainPalette[i++] = 0xe87878;
    MainPalette[i++] = 0xe89898;
    MainPalette[i++] = 0xc00010;
    MainPalette[i++] = 0x700000;
    i = 0;
    MainPaletteWater[i++] = 0x400000;
    MainPaletteWater[i++] = 0x900000;
    MainPaletteWater[i++] = 0xe00000;
    MainPaletteWater[i++] = 0x800000;
    MainPaletteWater[i++] = 0xb03000;
    MainPaletteWater[i++] = 0xe07000;
    MainPaletteWater[i++] = 0xe0a000;
    MainPaletteWater[i++] = 0xe0c000;
    MainPaletteWater[i++] = 0x200008;
    MainPaletteWater[i++] = 0x700010;
    MainPaletteWater[i++] = 0xe00020;
    MainPaletteWater[i++] = 0xe84848;
    MainPaletteWater[i++] = 0xe87878;
    MainPaletteWater[i++] = 0xe89898;
    MainPaletteWater[i++] = 0xc00010;
    MainPaletteWater[i++] = 0x700000;
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

int HCZMiniboss::OnHit() {
    InvulnTimer = 0x20;
    HitCount -= 1;
    if (HitCount == 0) {
        Scene->StopTimer = true;
        Scene->Score += 1000;
        HitCount = -1;
        return 0;
    }

    return 0;
}

void HCZMiniboss::HandleDamage() {
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
            if (this->Y > Scene->WaterLevel) {
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

void HCZMiniboss::Update() {
    int bodyLeft = 67;
    int bodyTop = 1;
    if (HitCount < 0) {
        if (ExplosionTimer > 0) {
            if (ExplosionTimer % 3 == 0) {
                Scene->AddExplosion(5, false, X + Math::randRange(-0x20, 0x20), Y + Math::randRange(-0x20, 0x20));
                Sound::Play(Sound::SFX_BOSSEXPLOSION);
            }

            ExplosionTimer--;
        }
        else {
            Scene->AddMovingSprite(Sprite, X, Y, bodyLeft, bodyTop, 32, 32, -32, -32, false, false, -0x400, -0x400, 0x38);
            Scene->AddMovingSprite(Sprite, X, Y, bodyLeft + 32, bodyTop, 32, 32, 0, -32, false, false, 0x400, -0x400, 0x38);
            Scene->AddMovingSprite(Sprite, X, Y, bodyLeft + 00, bodyTop + 32, 32, 32, -32, 0, false, false, -0x400, -0x400, 0x48);
            Scene->AddMovingSprite(Sprite, X, Y, bodyLeft + 32, bodyTop + 32, 32, 32, 0, 0, false, false, 0x400, -0x400, 0x48);
            Scene->AddNewObject(Obj_Signpost, 0x00, X, Scene->CameraY - 64, false, false);
            Active = false;
            App->Audio->FadeMusic(2.0);
        }
        return;
    }

    HandleDamage();
    if (!Started) {
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
        App->Audio->PushMusic(Sound::SoundBank[0xF1], true, 276105);
        Started = true;
    }

    if (SpinSpeed < 0x100) SpinSpeed += 0x1;

    TimerSpin += SpinSpeed;
    if (TimerSpin >= (Sprite->Animations[2].FrameCount * 512)) {
        TimerSpin = 0;
    }

    RocketTurn += 1;
    if (RocketTurn >= 0x40) {
        RocketTurn = 0x0;
    }

    Object::Update();
}

void HCZMiniboss::DrawRocket(int Rock, int Ang, int Flip, int Side, int CamX, int CamY) {
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

void HCZMiniboss::Render(int CamX, int CamY) {
    for (int i = 0; i < 0x41; i += 0x20)
{
        G->DrawSprite(Sprite, 1, TimerSpin >> 9, 0x3720 - CamX, 0x06F8 - CamY - i, 0, IE_NOFLIP);
    }
    G->DrawSprite(Sprite, 2, TimerSpin >> 9, 0x3720 - CamX, 0x06E0 - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 0, 2, 0x3720 - CamX, 0x06B8 - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 0, 3, 0x3720 - CamX, 0x06E0 - CamY, 0, IE_NOFLIP);
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


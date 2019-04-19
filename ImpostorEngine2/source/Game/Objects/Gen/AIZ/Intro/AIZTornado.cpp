// Object ID: 0xFFFFFFFF
// Object Name: AIZTornado.cpp

#include "AIZTornado.h"

typedef IMath Math;

void AIZTornado::Create() {
    Object::Create();
    Sprite = LevelScene::LoadSpriteFromBin("AIZ/Intro.bin", SaveGame::CurrentMode);
    if (Sprite) {
        Sprite->SetTransparentColorIndex(0);
        ShadowAnim = Sprite->FindAnimation("Shadow");
        PropellorAnim = Sprite->FindAnimation("Propellor");
        FlameAnim = Sprite->FindAnimation("Flame");
        HeadsAnim = Sprite->FindAnimation("Heads");
        TornadoAnim = Sprite->FindAnimation("Tornado");
    }

    HeadsFrame = 1;
    PlayerSprite = LevelScene::LoadSpriteFromBin("Players/AIZCutscene.bin", SaveGame::CurrentMode);
    if (PlayerSprite) {
        PlayerSprite->SetTransparentColorIndex(0);
    }

    X = App->WIDTH / 2 - 4;
    Y = App->HEIGHT / 2 - 16;
    SonicAnim = 0;
    SonicFrame = 0;
}

void AIZTornado::Update() {
    if (State == 0) {
        SonicFrameTimer++;
        if (SonicFrameTimer > 1) {
            SonicFrame++;
            if (SonicFrame > 1) SonicFrame = 0;

            SonicFrameTimer = 0;
        }

        Scene->Player->Visible = false;
        UpdateTimer++;
        if (UpdateTimer > 180) {
            State++;
            UpdateTimer = 0;
            UpdateTimer = this->Y;
        }

    }
    else if (State == 1) {
        SonicAnim = 1;
        SonicFrameTimer++;
        this->X -= 8;
        if (this->Y - 48 < UpdateTimer) {
            this->Y += 4;
        }

        if (SonicFrameTimer > 4) {
            SonicFrame++;
            if (SonicFrame > 4) {
                SonicFrame = 4;
            }

            SonicFrameTimer = 0;
        }

    }

    Object::Update();
}

void AIZTornado::Render(int CamX, int CamY) {
    if (!Visible || !Active) return;

    G->DrawSprite(Sprite, TornadoAnim, Frame, InitialX - CamX, InitialY - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, PropellorAnim, PropellorFrame, InitialX - CamX, InitialY - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, FlameAnim, FlameFrame, InitialX - CamX, InitialY - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, ShadowAnim, ShadowFrame, InitialX - CamX, InitialY - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, HeadsAnim, HeadsFrame, InitialX - CamX, InitialY - CamY, 0, IE_NOFLIP);
    G->DrawSprite(PlayerSprite, SonicAnim, SonicFrame, X, Y, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }


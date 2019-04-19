// Object ID: 0xFFFFFFFF
// Object Name: AIZTornado.cpp

#include "AIZTornado.h"

typedef IMath Math;

void AIZTornado::Create() {
    Object::Create();
    Priority = true;
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

    InitialX = App->WIDTH / 2 - 4;
    InitialY = App->HEIGHT / 2 - 16;
    X = App->WIDTH / 2 - 4;
    Y = App->HEIGHT / 2 - 16;
    X -= 1;
    Y -= 20;
    InitialX -= 31;
    InitialY += 25;
    Scene->CameraX = InitialX;
    Scene->CameraY = InitialY;
    SonicAnim = 0;
    SonicFrame = 0;
    ShadowFrame = 3;
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

        if (InitialX > Scene->CameraX + App->WIDTH + 128) {
            Visible = false;
        }

    }

    TornadoBob();
    FlameFrame++;
    if (FlameFrame > 1) {
        FlameFrame = 0;
    }

    PropellorFrame++;
    if (PropellorFrame > 3) {
        PropellorFrame = 0;
    }

    ShadowFrameTimer++;
    if (ShadowFrameTimer > 4) {
        ShadowFrame++;
        ShadowFrameTimer = 0;
        if (ShadowFrame > 5) {
            ShadowFrame = 0;
        }

    }

    InitialX += 16;
    X += 16;
    Object::Update();
}

void AIZTornado::TornadoBob() {
    TornadoBobTimer++;
    if (TornadoBobTimer >= 2) {
        TornadoBobTimer = 0;
        if (TornadoBobDir >= 1) {
            TornadoBobAmount++;
            if (TornadoBobAmount >= 3) {
                TornadoBobDir = -1;
            }

        }
        else if (TornadoBobDir <= -1) {
            TornadoBobAmount--;
            if (TornadoBobAmount <= -3) {
                TornadoBobDir = 1;
            }

        }
        else {
            TornadoBobDir = 1;
        }
    }

}

void AIZTornado::Render(int CamX, int CamY) {
    if (!Visible || !Active) return;

    G->DrawSprite(Sprite, TornadoAnim, Frame, InitialX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, PropellorAnim, PropellorFrame, InitialX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, FlameAnim, FlameFrame, InitialX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, ShadowAnim, ShadowFrame, InitialX, InitialY, 0, IE_NOFLIP);
	G->DrawSprite(Sprite, HeadsAnim, HeadsFrame, InitialX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
    G->DrawSprite(PlayerSprite, SonicAnim, SonicFrame, X, Y + TornadoBobAmount, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }


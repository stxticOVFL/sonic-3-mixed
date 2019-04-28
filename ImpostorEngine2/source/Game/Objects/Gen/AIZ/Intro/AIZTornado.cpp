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

    InitialX = App->WIDTH / 2 - 104;
    InitialY = App->HEIGHT / 2 - 16;
    X = InitialX;
    Y = InitialY;
    X -= 1;
    Y -= 20;
    InitialX -= 31;
    InitialY += 25;
    VisualX = InitialX;
    Scene->CameraX = InitialX;
    Scene->CameraY = InitialY;
    SonicAnim = 0;
    SonicFrame = 0;
    SonicVisible = true;
    ShadowFrame = 3;
    PebbleX = App->WIDTH + 16;
    PebbleY = -16;
    PebbleState = 0;
    Scene->CleanDuplicateObjects(ListID, ID);
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
            StoredX = Scene->CameraX;
            InitialFallFrame = Scene->Frame;
            UpdateTimer = 0;
            UpdateTimer = this->Y;
            PebbleState = 1;
        }

    }
    else if (State == 1) {
        SonicAnim = 1;
        SonicFrameTimer++;
        this->X -= 2;
        if (this->Y - 24 < UpdateTimer) this->Y += Math::abs(Scene->Frame - InitialFallFrame) / 4;

        if (SonicFrameTimer > 2) {
            SonicFrame++;
            if (SonicFrame > 4) {
                SonicFrame = 4;
            }

            SonicFrameTimer = 0;
        }

        if (Scene->RoutineNumber < 1) Scene->CameraX = StoredX;

        if (InitialX > Scene->CameraX + App->WIDTH + 128) {
        }

    }

    if (PebbleState == 1) {
        if (PebbleX > X) PebbleX -= 3;

        if (PebbleY < Y) PebbleY++;

        if (PebbleX <= X && PebbleY >= Y) {
            State++;
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
    if (InitialX >= App->WIDTH / 2 + 0x1C0 && InitialX <= 0x1DD0) {
        Scene->CameraX += 32;
        if (App->WIDTH / 2 + 0x1C0 <= Scene->CameraX) Scene->CameraX -= 4 * (State + 6);

        if (State) VisualX += 12;

        if (VisualX >= App->WIDTH / 2) {
            VisualX -= 4;
            X -= 4;
        }

    }
    else {
        if (State == 0) X += 16;

        VisualX += 16;
    }
    if (Scene->RoutineNumber == 1) {
        X = Scene->Player->EZX - Scene->CameraX;
        Y = Math::abs(Scene->Player->EZY - Scene->CameraY);
        SonicAnim = 2;
        SonicWaveTimer++;
        if (SonicWaveTimer >= 6) {
            if (Scene->CameraX < InitialX + 3000) {
                Scene->AddNewObject(Obj_AIZIntroSplash, X - 32, Y);
                SonicWaveTimer = 0;
            }

        }

        SonicFrameTimer++;
        if (SonicFrameTimer > 3) {
            SonicFrame++;
            if (SonicFrame > 1) SonicFrame = 0;

        }

        VisualX -= 16;
        SonicVisible = true;
    }

    if (Scene->RoutineNumber == 2) Visible = false;

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
    if (!Active) return;

    if (Visible) {
        G->DrawSprite(Sprite, TornadoAnim, Frame, VisualX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, PropellorAnim, PropellorFrame, VisualX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, FlameAnim, FlameFrame, VisualX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, ShadowAnim, ShadowFrame, VisualX, InitialY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, HeadsAnim, HeadsFrame, VisualX, InitialY + TornadoBobAmount, 0, IE_NOFLIP);
    }

    if (SonicVisible && Visible) G->DrawSprite(PlayerSprite, SonicAnim, SonicFrame, X, Y + ((Scene->RoutineNumber == 1) ? 0 : TornadoBobAmount), 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);

    if (PebbleState > 0) {
        G->DrawSprite(Sprite, Sprite->FindAnimation("Pebble"), 0, PebbleX, PebbleY, 0, IE_NOFLIP);
    }

    }


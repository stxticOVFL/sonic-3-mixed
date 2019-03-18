// Object ID: 0xB5
// Object Name: Stalagtite.cpp

#include "Stalagtite.h"

typedef IMath Math;

CONSTRUCTER Stalagtite::Stalagtite() {
    BinIndex = LevelScene::LoadSpriteBin("ICZ/Wall and Column.bin");
}

void Stalagtite::Create() {
    Object::Create();
    W = 32;
    H = 64;
    OGX = X;
    OGY = Y;
    SolidTop = true;
    Active = true;
    Priority = false;
    CurrentAnimation = Sprite->FindAnimation("Wall and Column");
    Frame = 5;
    Scene->AddSelfToRegistry(this, "Solid");
    Fallen = false;
    FallTimer = -1;
}

void Stalagtite::Update() {
    FallTimer = FallTimer == 0 ? 0 : (FallTimer != -1 ? FallTimer - 1 : -1);
    if (Math::pydistance(X, Y, Scene->Players[0]->X, Scene->Players[0]->Y) <= 0xA0 && !Fallen && FallTimer == -1) {
        FallTimer = 20;
    }

    if (FallTimer > 0) X = OGX + (FallTimer % 2 == 0 ? 0 : 2);
    else X = OGX;
    if (!Fallen && FallTimer == 0) Gravity = 0x40;

    if (Y > OGY + 0x80 && !Fallen) {
        Gravity = 0;
        YSpeed = 0;
        Fallen = true;
        Sound::Play(Sound::SFX_IMPACT5);
    }

    Object::Update();
}

int Stalagtite::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (HitFrom != CollideSide::TOP && Scene->Players[PlayerID]->Action != ActionType::Dead) Scene->Players[PlayerID]->Hurt(X, false);

    return 1;
}

void Stalagtite::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }


// Object ID: 0xB4
// Object Name: ICZSwingingPlatform.cpp

#include "ICZSwingingPlatform.h"

typedef IMath Math;

void ICZSwingingPlatform::Create() {
    Object::Create();
    Sprite = LevelScene::LoadSpriteFromBin("ICZ/Swinging Platform.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Swinging Platform");
    RingAnimation = Sprite->FindAnimation("Ring");
    W = 64;
    H = 16;
    Solid = true;
    VisualLayer = 1;
    Scene->AddSelfToRegistry(this, "Solid");
    Break = SubType == 2 ? true : false;
    Trigger = Scene->AddNewObject(Obj_SwingingPlatformTrigger, 0, X, Y, FlipX, false);
    Trigger->Parent = this;
    Y += 8;
    Pivot = 0x84;
}

void ICZSwingingPlatform::Update() {
    if (!Trigger) return;

    SubType = SubType == 0 ? 0 : SubType - 1;
    VisualCircle = SubType > 90 ? 90 : SubType;
    X = ((Math::sinHex(VisualCircle) * 0x50) >> 16) + InitialX;
    Trigger->X = X + (FlipX ? -28 : 28);
    Trigger->Y = Y - 16;
    Object::Update();
}

void ICZSwingingPlatform::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - 8 - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    G->DrawSprite(Sprite, RingAnimation, 0, InitialX - CamX, InitialY - Pivot - CamY, 0, IE_NOFLIP);
    }

int ICZSwingingPlatform::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    Player = Scene->Players[PlayerID];
    if (Player->GroundSpeed <= 0x10 || !Player->Ground || SubType != 0) return 0;

    SubType = Player->GroundSpeed / 2;
    return 1;
}


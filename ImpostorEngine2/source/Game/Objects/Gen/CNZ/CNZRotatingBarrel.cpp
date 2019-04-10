// Object ID: 0x47
// Object Name: CNZRotatingBarrel.cpp

#include "CNZRotatingBarrel.h"

typedef IMath Math;

void CNZRotatingBarrel::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    YSubtypeVelocity = 0;
    PositionOffset = 0;
    YSubtypeVelocity = (SubType >> 3) & 0x0e;
    Timer = 1;
    Frame = 0;
    W = 64;
    H = 64;
    VisW = 32;
    VisH = 32;
    Sprite = LevelScene::LoadSpriteFromBin("CNZ/Cylinder.bin", SaveGame::CurrentMode);
    CurrentAnimation = Sprite->FindAnimation("Cylinder");
}

void CNZRotatingBarrel::Update() {
    Object::Update();
}

void CNZRotatingBarrel::Render(int CamX, int CamY) {
    Timer -= 1;
    if (Timer < 0) {
        Timer = 1;
        Frame += 1;
        Frame = Frame & 3;
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int CNZRotatingBarrel::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    int16_t NewSpeed = YSpeed;
    if (Player == 0) {
        return false;
    }

    MoveSprite();
    PositionOffset = Player->Y - Y;
    if (PositionOffset == 0) {
        if (abs(NewSpeed) < 0x80) {
            YSpeed = 0;
        }

    }
    else if (PositionOffset < 0) {
        if (YSubtypeVelocity <= NewSpeed) {
            return true;
        }

        NewSpeed += 0x20;
        if (NewSpeed >= 0) {
            if (Player->InputDown) {
                NewSpeed += 0x20;
            }

        }
        else {
            NewSpeed += 0x10;
        }
        YSpeed = NewSpeed;
    }
    else {
        if (-YSubtypeVelocity >= NewSpeed) {
            return true;
        }

        NewSpeed -= 0x20;
        if (NewSpeed < 0) {
            if (Player->InputUp) {
                NewSpeed -= 0x20;
            }

        }
        else {
            NewSpeed -= 0x10;
        }
        YSpeed = NewSpeed;
    }
    return true;
}


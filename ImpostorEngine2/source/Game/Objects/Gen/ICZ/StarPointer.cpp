// Object ID: 0xAE
// Object Name: StarPointer.cpp

#include "StarPointer.h"

typedef IMath Math;

void StarPointer::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = Sprite->FindAnimation("Star Pointer");
    OrbXPos[0] = 0;
    OrbYPos[0] = 0;
    OrbXPos[1] = 0;
    OrbYPos[1] = 0;
    OrbXPos[2] = 0;
    OrbYPos[2] = 0;
    OrbXPos[3] = 0;
	OrbYPos[3] = 0;
	OrbOffsets[0] = 0;
	OrbOffsets[1] = 90;
    OrbOffsets[2] = 180;
    OrbOffsets[3] = 270;
	RotAngle = 0;
    TurnSpeed = 0.1;
}

void StarPointer::Update() {
    RotAngle = 0;
    RotAngle += OrbOffsets[0];
    RotAngle += TurnSpeed;
    OrbXPos[0] = sin(RotAngle) * 20 + this->X;
    OrbYPos[0] = cos(RotAngle) * 20 + this->Y;
    OrbOffsets[0] = RotAngle;
    RotAngle = 0;
    RotAngle += OrbOffsets[1];
    RotAngle += TurnSpeed;
    OrbXPos[1] = sin(RotAngle) * 20 + this->X;
    OrbYPos[1] = cos(RotAngle) * 20 + this->Y;
    OrbOffsets[1] = RotAngle;
    RotAngle = 0;
    RotAngle += OrbOffsets[2];
    RotAngle += TurnSpeed;
    OrbXPos[2] = sin(RotAngle) * 20 + this->X;
    OrbYPos[2] = cos(RotAngle) * 20 + this->Y;
    OrbOffsets[2] = RotAngle;
    RotAngle = 0;
    RotAngle += OrbOffsets[3];
    RotAngle += TurnSpeed;
    OrbXPos[3] = sin(RotAngle) * 20 + this->X;
    OrbYPos[3] = cos(RotAngle) * 20 + this->Y;
    OrbOffsets[3] = RotAngle;
    X -= 0.1;
    Object::Update();
}

void StarPointer::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
        G->DrawSprite(this->Sprite, CurrentAnimation, (Frame >> 8) + 1, OrbXPos[0] - CamX, OrbYPos[0] - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
        G->DrawSprite(this->Sprite, CurrentAnimation, (Frame >> 8) + 1, OrbXPos[1] - CamX, OrbYPos[1] - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
        G->DrawSprite(this->Sprite, CurrentAnimation, (Frame >> 8) + 1, OrbXPos[2] - CamX, OrbYPos[2] - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
        G->DrawSprite(this->Sprite, CurrentAnimation, (Frame >> 8) + 1, OrbXPos[3] - CamX, OrbYPos[3] - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    }


// Object ID: 0xFFFFFFFF
// Object Name: TensionBridgeChild.cpp

#include "TensionBridgeChild.h"

typedef IMath Math;

void TensionBridgeChild::Create() {
    Object::Create();
    this->W = 16;
    this->H = 16;
    this->Active = true;
    this->Priority = false;
    SolidTop = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Rotation = false;
}

void TensionBridgeChild::Update() {
    Object::Update();
}

void TensionBridgeChild::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }


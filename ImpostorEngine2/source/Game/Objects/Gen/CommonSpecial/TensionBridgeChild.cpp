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
    switch (Scene->ZoneID) {
        case 2:
        AutoAnimate = true;
        break;
        case 5:
        AutoAnimate = false;
        break;
    }

}

void TensionBridgeChild::Render(int CamX, int CamY) {
    if (Scene->ZoneID == 5 && Frame == 0 && AutoAnimate == true) {
        AutoAnimate = false;
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }


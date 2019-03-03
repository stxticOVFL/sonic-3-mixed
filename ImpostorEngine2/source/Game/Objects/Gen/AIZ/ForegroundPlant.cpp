// Object ID: 0x35
// Object Name: ForegroundPlant.cpp

#include "ForegroundPlant.h"

typedef IMath Math;

void ForegroundPlant::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    DoDeform = true;
    W = 1;
    H = 1;
    CamMult = (SubType >> 2) & 0x3C;
    Frame = (SubType & 0xF) & 1;
    VisualLayer = 1;
    CurrentAnimation = 21;
}

void ForegroundPlant::Render(int CamX, int CamY) {
    switch (CamMult) {
        case 0x04:
        X = (int32_t(InitialX) - 0xA0 - CamX) / 16 + InitialX;
        Y = (int32_t(InitialY) - 0x70 - CamY) / 16 + InitialY;
        break;
        case 0x08:
        X = (int32_t(InitialX) - 0xA0 - CamX) / 8 + InitialX;
        Y = (int32_t(InitialY) - 0x70 - CamY) / 8 + InitialY;
        break;
        case 0x0C:
        X = (int32_t(InitialX) - 0xA0 - CamX) / 4 + InitialX;
        Y = (int32_t(InitialY) - 0x70 - CamY) / 4 + InitialY;
        break;
        case 0x10:
        X = (int32_t(InitialX) - 0xA0 - CamX) / 2 + InitialX;
        Y = (int32_t(InitialY) - 0x70 - CamY) / 2 + InitialY;
        break;
        case 0x14:
        X = (int32_t(InitialX) - 0xA0 - CamX) + InitialX;
        Y = (int32_t(InitialY) - 0x70 - CamY) + InitialY;
        break;
        case 0x18:
        X = (int32_t(InitialX) - 0xA0 - CamX) * 2 + InitialX;
        Y = (int32_t(InitialY) - 0x70 - CamY) + InitialY;
        break;
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }


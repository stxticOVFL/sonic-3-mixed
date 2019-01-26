// Object ID: 0x2F
// Object Name: NonAnim.cpp

#include "NonAnim.h"

typedef IMath Math;

void NonAnim::Create() {
    Object::Create();
    Active = true;
    CurrentAnimation = -1;
    if (SubType == 0x06) {
        VisualLayer = 1;
        X++;
        VisW = 128;
        VisH = 96;
    }
    else if (SubType == 0x07) {
        VisualLayer = 1;
        VisW = 128;
        VisH = 96;
    }
    else if (SubType == 0x09) {
        VisualLayer = 1;
        VisW = 128;
        VisH = 96;
    }
    else if (SubType == 0x0A) {
        VisualLayer = 1;
        VisW = 128;
        VisH = 96;
    }
    else if (SubType == 0x13) {
        VisualLayer = 0;
        CurrentAnimation = 11;
    }

    switch (Scene->ZoneID) {
        case 1:
        {
            CurrentAnimation = 23;
            if (SubType <= 4) {
                Frame = SubType;
            }
            else if (SubType == 5) {
                Frame = 0;
                VisualLayer = 1;
            }

            break;
        }
        case 2:
        {
            CurrentAnimation = -1;
            if (SubType >= 0x06 && SubType >= 0x0A) {
                Frame = SubType - 0x06;
            }

            if (SubType >= 0x0F && SubType >= 0x13) {
                Frame = SubType - 0x0F;
            }

            Frame = 0;
            break;
        }
        case 3:
        {
            CurrentAnimation = 19;
            if (SubType >= 0x0B) {
                Frame = SubType - 0x0B;
            }

            break;
        }
        case 6:
        {
            CurrentAnimation = -1;
            if (SubType >= 0x14 && SubType <= 0x17) {
                Frame = SubType - 0x14;
            }

            break;
        }
    }

}

void NonAnim::Render(int CamX, int CamY) {
    if (CurrentAnimation == -1) return;

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX | FlipY << 1);
    }


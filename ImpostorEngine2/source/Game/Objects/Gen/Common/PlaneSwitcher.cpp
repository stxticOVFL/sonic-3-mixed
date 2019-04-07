// Object ID: 0xFFFFFFFF
// Object Name: PlaneSwitcher.cpp

#include "PlaneSwitcher.h"

typedef IMath Math;

void PlaneSwitcher::Create() {
    Object::Create();
    Active = true;
    AttributeValue* AttributeHolder;
    AttributeHolder = GetAttribute("Angle");
    Angle = AttributeHolder->ValInt32;
    AttributeHolder = GetAttribute("Flags");
    Flags = AttributeHolder->ValUint32;
    AttributeHolder = GetAttribute("OnPath");
    OnPath = AttributeHolder->ValBool;
    AttributeHolder = GetAttribute("Size");
    Size = AttributeHolder->ValUint32;
    if (Size <= 0) Size = 1;

    W = Size * 16;
    H = Size * 16;
}

void PlaneSwitcher::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int PlaneSwitcher::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    /*if (OnPath) {
        if (Scene->Players[PlayerID]->Ground) {
            int dot;
            dot = 0;
            dot += Scene->Players[PlayerID]->XSpeed * ((Math::cosHex(Angle) * Math::abs(Scene->Players[PlayerID]->XSpeed)) >> 16);
            dot += Scene->Players[PlayerID]->YSpeed * ((Math::sinHex(Angle) * Math::abs(Scene->Players[PlayerID]->YSpeed)) >> 16);
            if (dot > 0) {
                Scene->Players[PlayerID]->Layer = (Flags >> 3) & 1;
                Scene->Players[PlayerID]->VisualLayer = (Flags >> 2) & 1;
            }
            else {
                Scene->Players[PlayerID]->Layer = (Flags >> 1) & 1;
                Scene->Players[PlayerID]->VisualLayer = (Flags >> 0) & 1;
            }
        }

    }
    else {
        int dot;
        dot = 0;
        dot += Scene->Players[PlayerID]->XSpeed * ((Math::cosHex(Angle) * Math::abs(Scene->Players[PlayerID]->XSpeed)) >> 16);
        dot += Scene->Players[PlayerID]->YSpeed * ((Math::sinHex(Angle) * Math::abs(Scene->Players[PlayerID]->YSpeed)) >> 16);
        if (dot > 0) {
            Scene->Players[PlayerID]->Layer = (Flags >> 3) & 1;
            Scene->Players[PlayerID]->VisualLayer = (Flags >> 2) & 1;
        }
        else {
            Scene->Players[PlayerID]->Layer = (Flags >> 1) & 1;
            Scene->Players[PlayerID]->VisualLayer = (Flags >> 0) & 1;
        }
    }*/
    return 1;
}


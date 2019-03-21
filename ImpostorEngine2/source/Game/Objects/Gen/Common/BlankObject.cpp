// Object ID: 0xFFFFFFFF
// Object Name: BlankObject.cpp

#include "BlankObject.h"

typedef IMath Math;

void BlankObject::Create() {
    Object::Create();
    Active = true;
    AttributeValue* AttributeVal;
    AttributeVal = GetAttribute("zoneName");
    App->Print(0, "Object attribute = %s", AttributeVal->value_string);
}

void BlankObject::Update() {
    Object::Update();
}

void BlankObject::Render(int CamX, int CamY) {
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, X - (H / 2) - CamY, W, H, 0x000000);
        G->SetDrawAlpha(0xFF);
    }

    }


// Object ID: 0xFFFFFFFF
// Object Name: BlankObject.cpp

#include "BlankObject.h"

typedef IMath Math;

void BlankObject::Create() {
    Object::Create();
    Active = true;
    AttributeValue* AttributeVal;
    AttributeVal = GetAttribute("zoneName");
    if (AttributeVal) App->Print(0, AttributeVal->value_string);
}

void BlankObject::Update() {
    Object::Update();
}

void BlankObject::Render(int CamX, int CamY) {
    }


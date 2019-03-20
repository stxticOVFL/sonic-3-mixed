// Object ID: 0xFFFFFFFF
// Object Name: BlankObject.cpp

#include "BlankObject.h"

typedef IMath Math;

void BlankObject::Create() {
    Object::Create();
    Active = true;
}

void BlankObject::Update() {
    Object::Update();
}

void BlankObject::Render(int CamX, int CamY) {
    }


// Object ID: 0xFFFFFFFF
// Object Name: BlankObject.cpp

#include "BlankObject.h"

typedef IMath Math;

void BlankObject::Create() {
    Object::Create();
    Active = true;
}

PUBLIC void BlankObject::Render(int CamX, int CamY) {

	if (App->viewObjectCollision) {
		G->SetDrawAlpha(0x80);
		G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, 0xFFFFFF);
		G->SetDrawAlpha(0xFF);
	}
}
